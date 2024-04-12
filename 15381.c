bt_status_t btsock_l2cap_connect(const bt_bdaddr_t *bd_addr, int channel, int* sock_fd, int flags)
{
 return btsock_l2cap_listen_or_connect(NULL, bd_addr, channel, sock_fd, flags, 0);
}
