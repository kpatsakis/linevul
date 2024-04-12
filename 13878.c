gio_poll_dispatch_del(int32_t fd)
{
    struct gio_to_qb_poll *adaptor;
    crm_trace("Looking for fd=%d", fd);
    if (qb_array_index(gio_map, fd, (void**)&adaptor) == 0) {
        crm_trace("Marking adaptor %p unused (ref=%d)", adaptor, gio_adapter_refcount(adaptor));
        adaptor->is_used = QB_FALSE;
    }
    return 0;
}
