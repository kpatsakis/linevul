is_xioctl_allowed(u8 mode, int cmd)
{
    if(sizeof(xioctl_filter)-1 < cmd) {
        A_PRINTF("Filter for this cmd=%d not defined\n",cmd);
        return 0;
    }
    if(xioctl_filter[cmd] == 0xFF) return 0;
    if(xioctl_filter[cmd] & mode) return 0;
    return A_ERROR;
}
