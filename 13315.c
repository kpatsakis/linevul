static int uipc_check_fd_locked(tUIPC_CH_ID ch_id)
{
 if (ch_id >= UIPC_CH_NUM)
 return -1;


 if (SAFE_FD_ISSET(uipc_main.ch[ch_id].srvfd, &uipc_main.read_set))
 {
        BTIF_TRACE_EVENT("INCOMING CONNECTION ON CH %d", ch_id);

        uipc_main.ch[ch_id].fd = accept_server_socket(uipc_main.ch[ch_id].srvfd);

        BTIF_TRACE_EVENT("NEW FD %d", uipc_main.ch[ch_id].fd);

 if ((uipc_main.ch[ch_id].fd > 0) && uipc_main.ch[ch_id].cback)
 {
 /*  if we have a callback we should add this fd to the active set
                and notify user with callback event */
            BTIF_TRACE_EVENT("ADD FD %d TO ACTIVE SET", uipc_main.ch[ch_id].fd);
            FD_SET(uipc_main.ch[ch_id].fd, &uipc_main.active_set);
            uipc_main.max_fd = MAX(uipc_main.max_fd, uipc_main.ch[ch_id].fd);
 }

 if (uipc_main.ch[ch_id].fd < 0)
 {
            BTIF_TRACE_ERROR("FAILED TO ACCEPT CH %d (%s)", ch_id, strerror(errno));
 return -1;
 }

 if (uipc_main.ch[ch_id].cback)
            uipc_main.ch[ch_id].cback(ch_id, UIPC_OPEN_EVT);
 }


 if (SAFE_FD_ISSET(uipc_main.ch[ch_id].fd, &uipc_main.read_set))
 {

 if (uipc_main.ch[ch_id].cback)
            uipc_main.ch[ch_id].cback(ch_id, UIPC_RX_DATA_READY_EVT);
 }
 return 0;
}
