static void h2_session_ev_mpm_stopping(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_DONE:
            /* nop */
            break;
        default:
            h2_session_shutdown_notice(session);
            break;
    }
}
