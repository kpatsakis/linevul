size_t hashtable_iter_serial(void *iter)
{
    pair_t *pair = list_to_pair((list_t *)iter);
    return pair->serial;
}
