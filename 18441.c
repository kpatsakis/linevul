mainloop_add_fd(
    const char *name, int priority, int fd, void *userdata, struct mainloop_fd_callbacks *callbacks) 
{
    mainloop_io_t *client = NULL;
    if(fd > 0) {
        client = calloc(1, sizeof(mainloop_io_t));          
        client->name = strdup(name);
        client->userdata = userdata;

        if(callbacks) {
            client->destroy_fn = callbacks->destroy;
            client->dispatch_fn_io = callbacks->dispatch;
        }

        client->channel = g_io_channel_unix_new(fd);
        client->source = g_io_add_watch_full(
            client->channel, priority, (G_IO_IN|G_IO_HUP|G_IO_NVAL|G_IO_ERR),
            mainloop_gio_callback, client, mainloop_gio_destroy);

        /* Now that mainloop now holds a reference to adaptor->channel,
         * thanks to g_io_add_watch_full(), drop ours from g_io_channel_unix_new().
         *
         * This means that adaptor->channel will be free'd by:
         * g_main_context_dispatch() or g_source_remove()
         *  -> g_source_destroy_internal()
         *      -> g_source_callback_unref()
         * shortly after mainloop_gio_destroy() completes
         */
        g_io_channel_unref(client->channel);
        crm_trace("Added connection %d for %s[%p].%d %d", client->source, client->name, client, fd, mainloop_gio_refcount(client));
    }

    return client;
}
