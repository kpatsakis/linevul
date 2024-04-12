void *hashtable_iter_next(hashtable_t *hashtable, void *iter)
{
    list_t *list = (list_t *)iter;
    if(list->next == &hashtable->list)
        return NULL;
    return list->next;
}
