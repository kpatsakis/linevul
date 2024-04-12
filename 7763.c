static void timer_init(Unit *u) {
        Timer *t = TIMER(u);

        assert(u);
        assert(u->load_state == UNIT_STUB);

        t->next_elapse_monotonic_or_boottime = USEC_INFINITY;
        t->next_elapse_realtime = USEC_INFINITY;
        t->accuracy_usec = u->manager->default_timer_accuracy_usec;
}
