void qemu_spice_display_switch(SimpleSpiceDisplay *ssd,
                               DisplaySurface *surface)
{
    SimpleSpiceUpdate *update;
    bool need_destroy;

    dprint(1, "%s/%d:\n", __func__, ssd->qxl.id);

    memset(&ssd->dirty, 0, sizeof(ssd->dirty));
    if (ssd->surface) {
        pixman_image_unref(ssd->surface);
        ssd->surface = NULL;
        pixman_image_unref(ssd->mirror);
        ssd->mirror = NULL;
    }

    qemu_mutex_lock(&ssd->lock);
    need_destroy = (ssd->ds != NULL);
    ssd->ds = surface;
    while ((update = QTAILQ_FIRST(&ssd->updates)) != NULL) {
        QTAILQ_REMOVE(&ssd->updates, update, next);
        qemu_spice_destroy_update(ssd, update);
    }
    qemu_mutex_unlock(&ssd->lock);
    if (need_destroy) {
        qemu_spice_destroy_host_primary(ssd);
    }
    if (ssd->ds) {
        qemu_spice_create_host_primary(ssd);
    }

    memset(&ssd->dirty, 0, sizeof(ssd->dirty));
    ssd->notify++;
}
