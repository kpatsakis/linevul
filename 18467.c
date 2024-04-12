static uint32_t fdctrl_read_main_status(FDCtrl *fdctrl)
{
    uint32_t retval = fdctrl->msr;

    fdctrl->dsr &= ~FD_DSR_PWRDOWN;
    fdctrl->dor |= FD_DOR_nRESET;

    FLOPPY_DPRINTF("main status register: 0x%02x\n", retval);

    return retval;
}
