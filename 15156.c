void lbl_destroy()
{
    pthread_mutex_destroy(&(device.lbllock));
}
