e1000e_intrmgr_stop_timer(E1000IntrDelayTimer *timer)
{
    if (timer->running) {
        timer_del(timer->timer);
        timer->running = false;
    }
}
