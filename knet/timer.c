#include "timer.h"
#include "list.h"
#include "misc.h"

struct _ktimer_t {
    dlist_t*       current_list;  /* �������� */
    dlist_node_t*  list_node;     /* ����ڵ� */
    ktimer_loop_t* ktimer_loop;    /* ��ʱ��ѭ�� */
    ktimer_type_e  type;          /* ��ʱ������ */
    ktimer_cb_t    cb;            /* ��ʱ���ص� */
    void*          data;          /* �Զ������� */
    time_t         ms;            /* �´δ���ʱ�� */
    time_t         intval;        /* ��ʱ����� */
    int            times;         /* ���������� */
    int            current_times; /* ��ǰ�������� */
    int            stop;          /* ��ֹ��־ */
};

struct _ktimer_loop_t {
    dlist_t** ktimer_wheels; /* ʱ������������ */
    int       running;      /* ���б�־ */
    int       max_slot;     /* ʱ�������鳤�� */
    int       slot;         /* ��ǰ��λ */
    time_t    last_tick;    /* ��һ�ε���ѭ����ʱ�䣨���룩 */
    time_t    tick_intval;  /* ��λ�̶ȼ�������룩 */
};

int _ktimer_loop_select_slot(ktimer_loop_t* ktimer_loop, time_t ms);
void _ktimer_loop_add_timer(ktimer_loop_t* ktimer_loop, ktimer_t* timer);
void _ktimer_loop_add_ktimer_node(ktimer_loop_t* ktimer_loop, dlist_node_t* node, time_t ms);
dlist_node_t* _ktimer_loop_remove_timer(ktimer_t* timer);
int _ktimer_check_stop(ktimer_t* timer);

ktimer_loop_t* ktimer_loop_create(time_t freq, int slot) {
    int i = 0;
    ktimer_loop_t* ktimer_loop = create(ktimer_loop_t);
    assert(ktimer_loop);
    assert(freq);
    assert(slot);
    memset(ktimer_loop, 0, sizeof(ktimer_loop_t));
    ktimer_loop->max_slot     = slot;
    ktimer_loop->tick_intval  = freq;
    ktimer_loop->last_tick    = time_get_milliseconds();
    ktimer_loop->slot         = 1;
    ktimer_loop->ktimer_wheels = (dlist_t**)create_type(dlist_t, sizeof(dlist_t*) * ktimer_loop->max_slot);
    assert(ktimer_loop->ktimer_wheels);
    for (; i < ktimer_loop->max_slot; i++) {
        ktimer_loop->ktimer_wheels[i] = dlist_create();
        assert(ktimer_loop->ktimer_wheels[i]);
    }
    return ktimer_loop;
}

void ktimer_loop_destroy(ktimer_loop_t* ktimer_loop) {
    int i = 0;
    ktimer_t*      timer = 0;
    dlist_node_t* node  = 0;
    dlist_node_t* temp  = 0;
    assert(ktimer_loop);
    /* �������в������� */
    for (; i < ktimer_loop->max_slot; i++) {
        dlist_for_each_safe(ktimer_loop->ktimer_wheels[i], node, temp) {
            timer = (ktimer_t*)dlist_node_get_data(node);
            ktimer_destroy(timer);
        }
        dlist_destroy(ktimer_loop->ktimer_wheels[i]);
    }
    destroy(ktimer_loop->ktimer_wheels);
    destroy(ktimer_loop);
}

void ktimer_loop_run(ktimer_loop_t* ktimer_loop) {
    assert(ktimer_loop);
    ktimer_loop->running = 1;
    while (ktimer_loop->running) {
        thread_sleep_ms((int)ktimer_loop->tick_intval);
        ktimer_loop_run_once(ktimer_loop);
    }
}

void ktimer_loop_exit(ktimer_loop_t* ktimer_loop) {
    assert(ktimer_loop);
    ktimer_loop->running = 0;
}

int _ktimer_loop_select_slot(ktimer_loop_t* ktimer_loop, time_t ms) {
    /* ���㰴��ǰ��λ��λ�ã������ĸ���λ�ᴥ����ʱ�� */
    return (int)(ktimer_loop->slot + ms / ktimer_loop->tick_intval) % ktimer_loop->max_slot;
}

void _ktimer_loop_add_timer(ktimer_loop_t* ktimer_loop, ktimer_t* timer) {
    /* ��timer�����뵽�´����еĲ�λ�����δ���ڻᱻ������������λ */
    dlist_node_t* node = dlist_add_tail_node(ktimer_loop->ktimer_wheels[ktimer_loop->slot], timer);
    ktimer_set_current_list(timer, ktimer_loop->ktimer_wheels[ktimer_loop->slot]);
    ktimer_set_current_list_node(timer, node);
}

void _ktimer_loop_add_ktimer_node(ktimer_loop_t* ktimer_loop, dlist_node_t* node, time_t ms) {
    int slot = _ktimer_loop_select_slot(ktimer_loop, ms);
    ktimer_t* timer = (ktimer_t*)dlist_node_get_data(node);
    dlist_add_tail(ktimer_loop->ktimer_wheels[slot], node);
    ktimer_set_current_list(timer, ktimer_loop->ktimer_wheels[slot]);
}

dlist_node_t* _ktimer_loop_remove_timer(ktimer_t* timer) {
    dlist_t* current_list = ktimer_get_current_list(timer);
    dlist_node_t* list_node = ktimer_get_current_list_node(timer);
    dlist_remove(current_list, list_node);
    ktimer_set_current_list(timer, 0);
    return list_node;
} 

int ktimer_loop_run_once(ktimer_loop_t* ktimer_loop) {
    dlist_node_t* node   = 0;
    dlist_node_t* temp   = 0;
    dlist_t*      timers = 0;
    ktimer_t*      timer  = 0;
    time_t        ms     = time_get_milliseconds(); /* ��ǰʱ��������룩 */
    int           count  = 0;
    assert(ktimer_loop);
    timers = ktimer_loop->ktimer_wheels[ktimer_loop->slot];
    dlist_for_each_safe(timers, node, temp) {
        timer = (ktimer_t*)dlist_node_get_data(node);
        if (!_ktimer_check_stop(timer)) {
            /* ����ʱ�� */
            if (ktimer_check_timeout(timer, ms)) {
                count++;
            }
        } else {
            /* ���� */
            ktimer_destroy(timer);
        }
    }
    /* ��һ����λ */
    ktimer_loop->slot = (ktimer_loop->slot + 1) % ktimer_loop->max_slot;
    /* ��¼�ϴ�tickʱ��� */
    ktimer_loop->last_tick = ms;
    return count;
}

int _ktimer_check_stop(ktimer_t* timer) {
    return timer->stop;
}

ktimer_loop_t* ktimer_get_loop(ktimer_t* timer) {
    return timer->ktimer_loop;
}

void ktimer_set_current_list(ktimer_t* timer, dlist_t* list) {
    assert(timer); /* list����Ϊ�� */
    timer->current_list = list;
}

void ktimer_set_current_list_node(ktimer_t* timer, dlist_node_t* node) {
    assert(timer);
    assert(node);
    timer->list_node = node;
}

dlist_t* ktimer_get_current_list(ktimer_t* timer) {
    assert(timer);
    return timer->current_list;
}

dlist_node_t* ktimer_get_current_list_node(ktimer_t* timer) {
    assert(timer);
    return timer->list_node;
}

ktimer_t* ktimer_create(ktimer_loop_t* ktimer_loop) {
    ktimer_t* timer = 0;
    assert(ktimer_loop);
    timer = create(ktimer_t);
    assert(timer);
    memset(timer, 0, sizeof(ktimer_t));
    timer->ktimer_loop = ktimer_loop;
    return timer;
}

void ktimer_destroy(ktimer_t* timer) {
    assert(timer);
    assert(timer->current_list);
    assert(timer->list_node);
    dlist_delete(timer->current_list, timer->list_node);
    free(timer);
}

int ktimer_check_dead(ktimer_t* timer) {
    if (timer->type == ktimer_type_once) {
        return 1;
    } else if (timer->type == ktimer_type_times) {
        if (timer->times <= timer->current_times) {
            return 1;
        }
    }
    return 0;
}

time_t ktimer_loop_get_tick_intval(ktimer_loop_t* ktimer_loop) {
    return ktimer_loop->tick_intval;
}

int ktimer_check_timeout(ktimer_t* timer, time_t ms) {
    dlist_node_t* node        = 0;
    time_t        tick_intval = 0;
    ktimer_loop_t* ktimer_loop  = 0;
    assert(timer);
    ktimer_loop = timer->ktimer_loop;
    assert(ktimer_loop);
    tick_intval = ktimer_loop_get_tick_intval(ktimer_loop);
    if (timer->ms > ms) {
        /* �ڽ�����ʱ�䵽�ڣ�����Ƿ���Դ��� */
        if (timer->ms - ms >= tick_intval) {
            /* �����´γ�ʱʱ����ڣ����ڣ�һ��tick���, ���Ա��´δ���, ������������λ��λ */
            node = _ktimer_loop_remove_timer(timer);
            _ktimer_loop_add_ktimer_node(timer->ktimer_loop, node, timer->ms - ms);
            return 0;
        } else {
            /* �����´γ�ʱʱ��С��һ��tick���, �����һ�ִ����Ѿ��೬ʱ��һ��tick��� */
        }
    }
    if (timer->type == ktimer_type_times) {
        /* �ȸı���� */
        timer->ms = ms + timer->intval;
        timer->current_times++;
    }
    timer->cb(timer, timer->data);
    if (_ktimer_check_stop(timer)) {
        /* �ص��ڵ���ktimer_stop() */
        ktimer_destroy(timer);
        return 1;
    }
    if (timer->type == ktimer_type_once) {
        ktimer_destroy(timer);
    } else if (timer->type == ktimer_type_period) {
        timer->ms = ms + timer->intval;
        node = _ktimer_loop_remove_timer(timer);
        _ktimer_loop_add_ktimer_node(timer->ktimer_loop, node, timer->intval);
    } else if (timer->type == ktimer_type_times) {
        if (timer->times <= timer->current_times) {
            ktimer_destroy(timer);
        } else {
            node = _ktimer_loop_remove_timer(timer);
            _ktimer_loop_add_ktimer_node(timer->ktimer_loop, node, timer->intval);
        }
    }
    return 1;
}

int ktimer_stop(ktimer_t* timer) {
    assert(timer);
    timer->stop = 1;
    return error_ok;
}

int ktimer_start(ktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms) {
    assert(timer);
    assert(cb);
    assert(ms);
    if (timer->current_list) {
        return error_multiple_start;
    }
    timer->cb     = cb;
    timer->data   = data;
    timer->type   = ktimer_type_period;
    timer->ms     = time_get_milliseconds() + ms;
    timer->intval = ms;
    _ktimer_loop_add_timer(timer->ktimer_loop, timer);
    return error_ok;
}

int ktimer_start_once(ktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms) {
    assert(timer);
    assert(cb);
    assert(ms);
    if (timer->current_list) {
        return error_multiple_start;
    }
    timer->cb     = cb;
    timer->data   = data;
    timer->type   = ktimer_type_once;
    timer->ms     = time_get_milliseconds() + ms;
    timer->intval = ms;
    _ktimer_loop_add_timer(timer->ktimer_loop, timer);
    return error_ok;
}

int ktimer_start_times(ktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms, int times) {
    assert(timer);
    assert(cb);
    assert(ms);
    if (timer->current_list) {
        return error_multiple_start;
    }
    timer->cb     = cb;
    timer->data   = data;
    timer->type   = ktimer_type_times;
    timer->times  = times;
    timer->ms     = time_get_milliseconds() + ms;
    timer->intval = ms;
    _ktimer_loop_add_timer(timer->ktimer_loop, timer);
    return error_ok;
}
