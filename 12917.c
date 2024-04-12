static JSON_INLINE void list_insert(list_t *list, list_t *node)
{
    node->next = list;
    node->prev = list->prev;
    list->prev->next = node;
    list->prev = node;
}
