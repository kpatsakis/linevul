static void fdctrl_stop_transfer(FDCtrl *fdctrl, uint8_t status0,
                                 uint8_t status1, uint8_t status2)
{
    FDrive *cur_drv;
    cur_drv = get_cur_drv(fdctrl);

    fdctrl->status0 &= ~(FD_SR0_DS0 | FD_SR0_DS1 | FD_SR0_HEAD);
    fdctrl->status0 |= GET_CUR_DRV(fdctrl);
    if (cur_drv->head) {
        fdctrl->status0 |= FD_SR0_HEAD;
    }
    fdctrl->status0 |= status0;

    FLOPPY_DPRINTF("transfer status: %02x %02x %02x (%02x)\n",
                   status0, status1, status2, fdctrl->status0);
    fdctrl->fifo[0] = fdctrl->status0;
    fdctrl->fifo[1] = status1;
    fdctrl->fifo[2] = status2;
    fdctrl->fifo[3] = cur_drv->track;
    fdctrl->fifo[4] = cur_drv->head;
    fdctrl->fifo[5] = cur_drv->sect;
    fdctrl->fifo[6] = FD_SECTOR_SC;
    fdctrl->data_dir = FD_DIR_READ;
    if (!(fdctrl->msr & FD_MSR_NONDMA)) {
        DMA_release_DREQ(fdctrl->dma_chann);
    }
    fdctrl->msr |= FD_MSR_RQM | FD_MSR_DIO;
    fdctrl->msr &= ~FD_MSR_NONDMA;

    fdctrl_set_fifo(fdctrl, 7);
    fdctrl_raise_irq(fdctrl);
}
