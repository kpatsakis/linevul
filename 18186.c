static int zgetfilename(i_ctx_t *i_ctx_p)
{
    os_ptr op = osp;
    uint fnlen;
    gs_const_string pfname;
    stream *s;
    byte *sbody;
    int code;

    check_ostack(1);
    check_read_type(*op, t_file);

    s = (op)->value.pfile;

    code = sfilename(s, &pfname);
    if (code < 0) {
        pfname.size = 0;
    }

    fnlen = pfname.size;
    sbody = ialloc_string(fnlen, ".getfilename");
    if (sbody == 0) {
        code = gs_note_error(gs_error_VMerror);
        return code;
    }
    memcpy(sbody, pfname.data, fnlen);
    make_string(op, a_readonly | icurrent_space, fnlen, sbody);

    return 0;
}
