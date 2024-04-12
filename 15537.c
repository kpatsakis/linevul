static int timer_serialize(Unit *u, FILE *f, FDSet *fds) {
        Timer *t = TIMER(u);

        assert(u);
        assert(f);
        assert(fds);

        unit_serialize_item(u, f, "state", timer_state_to_string(t->state));
        unit_serialize_item(u, f, "result", timer_result_to_string(t->result));

        if (t->last_trigger.realtime > 0)
                unit_serialize_item_format(u, f, "last-trigger-realtime", "%" PRIu64, t->last_trigger.realtime);

        if (t->last_trigger.monotonic > 0)
                unit_serialize_item_format(u, f, "last-trigger-monotonic", "%" PRIu64, t->last_trigger.monotonic);

        return 0;
}
