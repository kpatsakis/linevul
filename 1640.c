int uipc_start_main_server_thread(void)
{
    uipc_main.running = 1;

 if (pthread_create(&uipc_main.tid, (const pthread_attr_t *) NULL, (void*)uipc_read_task, NULL) < 0)
 {
        BTIF_TRACE_ERROR("uipc_thread_create pthread_create failed:%d", errno);
 return -1;
 }

 return 0;
}
