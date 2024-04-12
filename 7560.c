static void cleanup_streams(h2_session *session)
{
    stream_sel_ctx ctx;
    ctx.session = session;
    ctx.candidate = NULL;
    while (1) {
        h2_mplx_stream_do(session->mplx, find_cleanup_stream, &ctx);
        if (ctx.candidate) {
            h2_session_stream_done(session, ctx.candidate);
            ctx.candidate = NULL;
        }
        else {
            break;
        }
    }
}
