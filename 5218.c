static void fdctrl_handle_powerdown_mode(FDCtrl *fdctrl, int direction)
{
    fdctrl->pwrd = fdctrl->fifo[1];
    fdctrl->fifo[0] = fdctrl->fifo[1];
    fdctrl_set_fifo(fdctrl, 1);
}
