static SpiceWatch *dummy_watch_add(int fd, int event_mask, SpiceWatchFunc func, void *opaque)
{
    return NULL; // apparently allowed?
}
