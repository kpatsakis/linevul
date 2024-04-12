zcurrentcolor(i_ctx_t * i_ctx_p)
{
    os_ptr                  op = osp;
    const gs_color_space *  pcs = gs_currentcolorspace(igs);
    const gs_client_color * pcc = gs_currentcolor(igs);
    int                     i, n = cs_num_components(pcs);
    bool                    push_pattern = n < 0;

    /* check for pattern */
    if (push_pattern) {
        gs_pattern_instance_t * pinst = pcc->pattern;

        if (pinst == 0 || !pattern_instance_uses_base_space(pinst))
            n = 1;
        else
            n = -n;
    }

    /* check for sufficient space on the stack */
    push(n);
    op -= n - 1;

    /* push the numeric operands, if any */
    if (push_pattern)
        --n;
    for (i = 0; i < n; i++, op++) {
        float   rval = pcc->paint.values[i];
        int     ival = (int)rval;

        /* the following handles indexed color spaces */
        if (rval == ival && pcs->type->index == gs_color_space_index_Indexed)
            make_int(op, ival);
        else
            make_real(op, rval);
    }

    /* push the pattern dictionary or null object, if appropriate */
    if (push_pattern)
        *op = istate->pattern[0];

    return 0;
}
