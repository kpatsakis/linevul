static void h2_session_ev_init(h2_session *session, int arg, const char *msg)
{
    switch (session->state) {
        case H2_SESSION_ST_INIT:
            transit(session, "init", H2_SESSION_ST_BUSY);
            break;
        default:
            /* nop */
            break;
    }
}
