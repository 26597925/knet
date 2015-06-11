#include <math.h>

#include "timer.h"
#include "list.h"
#include "misc.h"

struct _timer_t {
    dlist_t*      current_list;  /* �������� */
    dlist_node_t* list_node;     /* ����ڵ� */
    timer_loop_t* timer_loop;    /* ��ʱ��ѭ�� */
    timer_type_e  type;          /* ��ʱ������ */
    timer_cb_t    cb;            /* ��ʱ���ص� */
    void*         data;          /* �Զ������� */
    time_t        ms;            /* �´δ���ʱ�� */
    time_t        intval;        /* ��ʱ����� */
    int           times;         /* ���������� */
    int           current_times; /* ��ǰ�������� */
};

struct _timer_loop_t {
    dlist_t** timer_wheels; /* ʱ������������ */
    int       running;      /* ���б�־ */
    int       max_slot;     /* ʱ�������鳤�� */
    int       slot;         /* ��ǰ��λ */
    time_t    last_tick;    /* ��һ�ε���ѭ����ʱ�䣨���룩 */
    time_t    tick_intval;  /* ��λ�̶ȼ�������룩 */
};

int _timer_loop_select_slot(timer_loop_t* timer_loop, time_t ms);
void _timer_loop_add_timer(timer_loop_t* timer_loop, timer_t* timer);
void _timer_loop_add_timer_node(timer_loop_t* timer_loop, dlist_node_t* node, time_t ms);
dlist_node_t* _timer_loop_remove_timer(timer_t* timer);

timer_loop_t* timer_loop_create(time_t freq, int slot) {
    int i = 0;
    timer_loop_t* timer_loop = create(timer_loop_t);
    assert(timer_loop);
    memset(timer_loop, 0, sizeof(timer_loop_t));
    timer_loop->max_slot     = slot;
    timer_loop->tick_intval  = freq;
    timer_loop->last_tick    = time_get_milliseconds();
    timer_loop->slot         = 1;
    timer_loop->timer_wheels = (dlist_t**)create_type(dlist_t, sizeof(dlist_t*) * timer_loop->max_slot);
    assert(timer_loop->timer_wheels);
    for (; i < timer_loop->max_slot; i++) {
        timer_loop->timer_wheels[i] = dlist_create();
        assert(timer_loop->timer_wheels[i]);
    }
    return timer_loop;
}

void timer_loop_destroy(timer_loop_t* timer_loop) {
    int i = 0;
    timer_t*      timer = 0;
    dlist_node_t* node  = 0;
    dlist_node_t* temp  = 0;
    assert(timer_loop);
    /* �������в������� */
    for (; i < timer_loop->max_slot; i++) {
        dlist_for_each_safe(timer_loop->timer_wheels[i], node, temp) {
            timer = (timer_t*)dlist_node_get_data(node);
            timer_destroy(timer);
        }
        dlist_destroy(timer_loop->timer_wheels[i]);
    }
    destroy(timer_loop->timer_wheels);
    destroy(timer_loop);
}

void timer_loop_run(timer_loop_t* timer_loop) {
    timer_loop->running = 1;
    while (timer_loop->running) {
        thread_sleep_ms((int)timer_loop->tick_intval);
        timer_loop_run_once(timer_loop);
    }
}

void timer_loop_exit(timer_loop_t* timer_loop) {
    timer_loop->running = 0;
}

int _timer_loop_select_slot(timer_loop_t* timer_loop, time_t ms) {
    /* ���㰴��ǰ��λ��λ�ã������ĸ���λ�ᴥ����ʱ�� */
    return (int)(timer_loop->slot + ms / timer_loop->tick_intval) % timer_loop->max_slot;
}

void _timer_loop_add_timer(timer_loop_t* timer_loop, timer_t* timer) {
    /* ��timer�����뵽�´����еĲ�λ�����δ���ڻᱻ������������λ */
    dlist_node_t* node = dlist_add_tail_node(timer_loop->timer_wheels[timer_loop->slot], timer);
    timer_set_current_list(timer, timer_loop->timer_wheels[timer_loop->slot]);
    timer_set_current_list_node(timer, node);
}

void _timer_loop_add_timer_node(timer_loop_t* timer_loop, dlist_node_t* node, time_t ms) {
    int slot = _timer_loop_select_slot(timer_loop, ms);
    dlist_add_tail(timer_loop->timer_wheels[slot], node);
}

dlist_node_t* _timer_loop_remove_timer(timer_t* timer) {
    dlist_t* current_list = timer_get_current_list(timer);
    dlist_node_t* list_node = timer_get_current_list_node(timer);
    dlist_remove(current_list, list_node);
    return list_node;
} 

int timer_loop_run_once(timer_loop_t* timer_loop) {
    dlist_node_t* node   = 0;
    dlist_node_t* temp   = 0;
    dlist_t*      timers = 0;
    timer_t*      timer  = 0;
    time_t        ms     = time_get_milliseconds(); /* ��ǰʱ��������룩 */
    int           count  = 0;
    assert(timer_loop);
    timers = timer_loop->timer_wheels[timer_loop->slot];
    dlist_for_each_safe(timers, node, temp) {
        timer = (timer_t*)dlist_node_get_data(node);
        /* ����ʱ�� */
        if (timer_check_timeout(timer, ms)) {
            count++;
        }
    }
    /* ��һ����λ */
    timer_loop->slot = (timer_loop->slot + 1) % timer_loop->max_slot;
    /* ��¼�ϴ�tickʱ��� */
    timer_loop->last_tick = ms;
    return count;
}

timer_loop_t* timer_get_loop(timer_t* timer) {
    return timer->timer_loop;
}

void timer_set_current_list(timer_t* timer, dlist_t* list) {
    assert(timer);
    assert(list);
    timer->current_list = list;
}

void timer_set_current_list_node(timer_t* timer, dlist_node_t* node) {
    assert(timer);
    assert(node);
    timer->list_node = node;
}

dlist_t* timer_get_current_list(timer_t* timer) {
    assert(timer);
    return timer->current_list;
}

dlist_node_t* timer_get_current_list_node(timer_t* timer) {
    assert(timer);
    return timer->list_node;
}

timer_t* timer_create(timer_loop_t* timer_loop) {
    timer_t* timer = 0;
    assert(timer_loop);
    timer = create(timer_t);
    assert(timer);
    memset(timer, 0, sizeof(timer_t));
    timer->timer_loop = timer_loop;
    return timer;
}

void timer_destroy(timer_t* timer) {
    assert(timer);
    assert(timer->current_list);
    assert(timer->list_node);
    dlist_delete(timer->current_list, timer->list_node);
    free(timer);
}

int timer_check_dead(timer_t* timer) {
    if (timer->type == timer_type_once) {
        return 1;
    } else if (timer->type == timer_type_times) {
        if (timer->times <= timer->current_times) {
            return 1;
        }
    }
    return 0;
}

time_t timer_loop_get_tick_intval(timer_loop_t* timer_loop) {
    return timer_loop->tick_intval;
}

int timer_check_timeout(timer_t* timer, time_t ms) {
    dlist_node_t* node        = 0;
    time_t        tick_intval = 0;
    timer_loop_t* timer_loop  = 0;
    assert(timer);
    timer_loop = timer->timer_loop;
    assert(timer_loop);
    tick_intval = timer_loop_get_tick_intval(timer_loop);
    if (timer->ms > ms) {
        /* �ڽ�����ʱ�䵽�ڣ�����Ƿ���Դ��� */
        if (timer->ms - ms >= tick_intval) {
            /* �����´γ�ʱʱ����ڣ����ڣ�һ��tick���, ���Ա��´δ���, ������������λ��λ */
            node = _timer_loop_remove_timer(timer);
            _timer_loop_add_timer_node(timer->timer_loop, node, timer->ms - ms);
            return 0;
        } else {
            /* �����´γ�ʱʱ��С��һ��tick���, �����һ�ִ����Ѿ��೬ʱ��һ��tick��� */
        }
    }
    timer->cb(timer, timer->data);
    if (timer->type == timer_type_once) {
        timer_destroy(timer);
    } else if (timer->type == timer_type_period) {
        timer->ms = ms + timer->intval;
        node = _timer_loop_remove_timer(timer);
        _timer_loop_add_timer_node(timer->timer_loop, node, timer->intval);
    } else if (timer->type == timer_type_times) {
        timer->ms = ms + timer->intval;
        timer->current_times++;
        if (timer->times <= timer->current_times) {
            timer_destroy(timer);
        } else {
            node = _timer_loop_remove_timer(timer);
            _timer_loop_add_timer_node(timer->timer_loop, node, timer->intval);
        }
    }
    return 1;
}

int timer_stop(timer_t* timer) {
    assert(timer);
    timer_destroy(timer);
    return error_ok;
}

int timer_start(timer_t* timer, timer_cb_t cb, void* data, time_t ms) {
    assert(timer);
    assert(cb);
    assert(ms);
    timer->cb     = cb;
    timer->data   = data;
    timer->type   = timer_type_period;
    timer->ms     = time_get_milliseconds() + ms;
    timer->intval = ms;
    _timer_loop_add_timer(timer->timer_loop, timer);
    return error_ok;
}

int timer_start_once(timer_t* timer, timer_cb_t cb, void* data, time_t ms) {
    assert(timer);
    assert(cb);
    assert(ms);
    timer->cb     = cb;
    timer->data   = data;
    timer->type   = timer_type_once;
    timer->ms     = time_get_milliseconds() + ms;
    timer->intval = ms;
    _timer_loop_add_timer(timer->timer_loop, timer);
    return error_ok;
}

int timer_start_times(timer_t* timer, timer_cb_t cb, void* data, time_t ms, int times) {
    assert(timer);
    assert(cb);
    assert(ms);
    timer->cb     = cb;
    timer->data   = data;
    timer->type   = timer_type_times;
    timer->times  = times;
    timer->ms     = time_get_milliseconds() + ms;
    timer->intval = ms;
    _timer_loop_add_timer(timer->timer_loop, timer);
    return error_ok;
}
