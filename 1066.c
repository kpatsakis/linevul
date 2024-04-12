mainloop_child_destroy(mainloop_child_t *child)
{
    if (child->timerid != 0) {
        crm_trace("Removing timer %d", child->timerid);
        g_source_remove(child->timerid);
        child->timerid = 0;
    }

    free(child->desc);
    g_free(child);
}
