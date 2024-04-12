pdf14_forward_device_procs(gx_device * dev)
{
    gx_device_forward * pdev = (gx_device_forward *)dev;

    /*
     * We are using gx_device_forward_fill_in_procs to set the various procs.
     * This will ensure that any new device procs are also set.  However that
     * routine only changes procs which are NULL.  Thus we start by setting all
     * procs to NULL.
     */
    memset(&(pdev->procs), 0, size_of(pdev->procs));
    gx_device_forward_fill_in_procs(pdev);
    /*
     * gx_device_forward_fill_in_procs does not forward all procs.
     * Set the remainding procs to also forward.
     */
    set_dev_proc(dev, close_device, gx_forward_close_device);
    set_dev_proc(dev, fill_rectangle, gx_forward_fill_rectangle);
    set_dev_proc(dev, fill_rectangle_hl_color, gx_forward_fill_rectangle_hl_color);
    set_dev_proc(dev, tile_rectangle, gx_forward_tile_rectangle);
    set_dev_proc(dev, copy_mono, gx_forward_copy_mono);
    set_dev_proc(dev, copy_color, gx_forward_copy_color);
    set_dev_proc(dev, get_page_device, gx_forward_get_page_device);
    set_dev_proc(dev, strip_tile_rectangle, gx_forward_strip_tile_rectangle);
    set_dev_proc(dev, copy_alpha, gx_forward_copy_alpha);
    set_dev_proc(dev, get_profile, gx_forward_get_profile);
    set_dev_proc(dev, set_graphics_type_tag, gx_forward_set_graphics_type_tag);
    /* These are forwarding devices with minor tweaks. */
    set_dev_proc(dev, open_device, pdf14_forward_open_device);
    set_dev_proc(dev, put_params, pdf14_forward_put_params);
}
