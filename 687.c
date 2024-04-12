static uint64_t ns_to_ticks(uint64_t value)
{
    return (muldiv64(value, FS_PER_NS, HPET_CLK_PERIOD));
}
