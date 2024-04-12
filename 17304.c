static uint32_t fdctrl_read_statusB(FDCtrl *fdctrl)
{
    uint32_t retval = fdctrl->srb;

    FLOPPY_DPRINTF("status register B: 0x%02x\n", retval);

    return retval;
}
