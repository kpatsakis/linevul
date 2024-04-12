void UIPC_Init(void *p_data)
{
    UNUSED(p_data);

    BTIF_TRACE_DEBUG("UIPC_Init");

    memset(&uipc_main, 0, sizeof(tUIPC_MAIN));

    uipc_main_init();

    uipc_start_main_server_thread();
}
