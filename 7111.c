void qemu_spice_destroy_primary_surface(SimpleSpiceDisplay *ssd,
                                        uint32_t id, qxl_async_io async)
{
    trace_qemu_spice_destroy_primary_surface(ssd->qxl.id, id, async);
    if (async != QXL_SYNC) {
        spice_qxl_destroy_primary_surface_async(&ssd->qxl, id,
                (uintptr_t)qxl_cookie_new(QXL_COOKIE_TYPE_IO,
                                          QXL_IO_DESTROY_PRIMARY_ASYNC));
    } else {
        spice_qxl_destroy_primary_surface(&ssd->qxl, id);
    }
}
