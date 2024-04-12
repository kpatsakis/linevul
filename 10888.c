void wifi_socket_set_local_port(struct nl_sock *sock, uint32_t port)
{
 uint32_t pid = getpid() & 0x3FFFFF;
    nl_socket_set_local_port(sock, pid + (port << 22));
}
