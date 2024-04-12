static json_t *json_object_deep_copy(const json_t *object)
{
    json_t *result;
    void *iter;

    result = json_object();
    if(!result)
        return NULL;

    /* Cannot use json_object_foreach because object has to be cast
       non-const */
    iter = json_object_iter((json_t *)object);
    while(iter) {
        const char *key;
        const json_t *value;
        key = json_object_iter_key(iter);
        value = json_object_iter_value(iter);

        json_object_set_new_nocheck(result, key, json_deep_copy(value));
        iter = json_object_iter_next((json_t *)object, iter);
    }

    return result;
}
