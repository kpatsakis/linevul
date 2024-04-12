local_notify_destroy_callback(gpointer data)
{
    cib_local_notify_t *notify = data;

    free_xml(notify->notify_src);
    free(notify->client_id);
    free(notify);
}
