int ws_svr_broadcast_text(ws_svr *svr, char *message)
{
    return broadcast_message(svr, 0x1, message, strlen(message));
}
