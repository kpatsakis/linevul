clump_splay_walk_bwd_init(clump_splay_walker *sw, const gs_ref_memory_t *mem)
{
    clump_t *cp = mem->root;

    if (cp)
    {
        SANITY_CHECK(cp);

        sw->from = SPLAY_FROM_RIGHT;
        while (cp->right)
        {
            cp = cp->right;
        }
    }
    sw->cp = cp;
    sw->end = NULL;
    return cp;
}
