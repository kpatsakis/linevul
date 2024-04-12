e1000e_intrmgr_fire_all_timers(E1000ECore *core)
{
    int i;
    uint32_t val = e1000e_intmgr_collect_delayed_causes(core);

    trace_e1000e_irq_adding_delayed_causes(val, core->mac[ICR]);
    core->mac[ICR] |= val;

    if (core->itr.running) {
        timer_del(core->itr.timer);
        e1000e_intrmgr_on_throttling_timer(&core->itr);
    }

    for (i = 0; i < E1000E_MSIX_VEC_NUM; i++) {
        if (core->eitr[i].running) {
            timer_del(core->eitr[i].timer);
            e1000e_intrmgr_on_msix_throttling_timer(&core->eitr[i]);
        }
    }
}
