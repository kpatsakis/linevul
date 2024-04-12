CJSON_PUBLIC(void *) cJSON_malloc(size_t size)
{
    return global_hooks.allocate(size);
}
