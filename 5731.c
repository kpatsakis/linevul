void btif_hl_display_calling_process_name(void)
{
 char name[16];
    prctl(BTIF_IF_GET_NAME, name, 0, 0, 0);
    BTIF_TRACE_DEBUG("Process name (%s)", name);
}
