gsicc_manager_finalize(const gs_memory_t *memory, void * vptr)
{
    gsicc_manager_t *icc_man = (gsicc_manager_t *)vptr;

    gsicc_manager_free_contents(icc_man, "gsicc_manager_finalize");
}
