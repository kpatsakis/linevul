static int timer_load(Unit *u) {
        Timer *t = TIMER(u);
        int r;

        assert(u);
        assert(u->load_state == UNIT_STUB);

        r = unit_load_fragment_and_dropin(u);
        if (r < 0)
                return r;

        if (u->load_state == UNIT_LOADED) {

                if (set_isempty(u->dependencies[UNIT_TRIGGERS])) {
                        Unit *x;

                        r = unit_load_related_unit(u, ".service", &x);
                        if (r < 0)
                                return r;

                        r = unit_add_two_dependencies(u, UNIT_BEFORE, UNIT_TRIGGERS, x, true);
                        if (r < 0)
                                return r;
                }

                r = timer_setup_persistent(t);
                if (r < 0)
                        return r;

                r = timer_add_default_dependencies(t);
                if (r < 0)
                        return r;
        }

        return timer_verify(t);
}
