const char *json_object_iter_key(void *iter)
{
    if(!iter)
        return NULL;

    return hashtable_iter_key(iter);
}
