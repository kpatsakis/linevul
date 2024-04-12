static void btsock_l2cap_free(l2cap_socket *sock)
{
    pthread_mutex_lock(&state_lock);
    btsock_l2cap_free_l(sock);
    pthread_mutex_unlock(&state_lock);
}
