#include "example_config.h"

#if COMPILE_TIMER

#include "knet.h"

void ktimer_once_cb(ktimer_t* timer, void* data) {
    printf("once timer timeout\n");
}

void ktimer_times_cb(ktimer_t* timer, void* data) {
    ktimer_loop_t* loop = ktimer_get_loop(timer);
    printf("times timer timeout\n");
    if (ktimer_check_dead(timer)) {
        ktimer_loop_exit(loop);
    }
}

#define MAX_TIMES 5 /* ����5�� */

void ktimer_cb(ktimer_t* timer, void* data) {
    printf("peroid timer timeout\n");
}

int main() {
    ktimer_loop_t* loop = ktimer_loop_create(1000, 128);
    ktimer_t* ktimer_once = ktimer_create(loop);
    ktimer_t* ktimer_period = ktimer_create(loop);
    ktimer_t* ktimer_times = ktimer_create(loop);
    /* ����һ��ִ��һ�εĶ�ʱ�� */
    ktimer_start_once(ktimer_once, ktimer_once_cb, 0, 1000);
    /* ����һ��ִ�����޴εĶ�ʱ�� */
    ktimer_start(ktimer_period, ktimer_cb, 0, 1000);
    /* ����һ��ִ��5�εĶ�ʱ�� */
    ktimer_start_times(ktimer_times, ktimer_times_cb, 0, 1000, MAX_TIMES);
    ktimer_loop_run(loop);
    return 0;
}

#endif /* COMPILE_TIMER */
