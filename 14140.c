e1000e_set_ics(E1000ECore *core, int index, uint32_t val)
{
    trace_e1000e_irq_write_ics(val);
    e1000e_set_interrupt_cause(core, val);
}
