static uint64_t fdctrl_read_mem (void *opaque, hwaddr reg,
                                 unsigned ize)
{
    return fdctrl_read(opaque, (uint32_t)reg);
}
