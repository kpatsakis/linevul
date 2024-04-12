DefragContextDestroy(DefragContext *dc)
{
    if (dc == NULL)
        return;

    PoolFree(dc->frag_pool);
    SCFree(dc);
}
