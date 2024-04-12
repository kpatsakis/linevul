apr_status_t h2_session_pre_close(h2_session *session, int async)
{
    ap_log_cerror(APLOG_MARK, APLOG_TRACE1, 0, session->c, 
                  "h2_session(%ld): pre_close", session->id);
    dispatch_event(session, H2_SESSION_EV_PRE_CLOSE, 0, 
        (session->state == H2_SESSION_ST_IDLE)? "timeout" : NULL);
    return APR_SUCCESS;
}
