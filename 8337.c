static int server_finish(SSL *s)
{
    unsigned char *p;

    if (s->state == SSL2_ST_SEND_SERVER_FINISHED_A) {
        p = (unsigned char *)s->init_buf->data;
        *(p++) = SSL2_MT_SERVER_FINISHED;

        if (s->session->session_id_length > sizeof s->session->session_id) {
            SSLerr(SSL_F_SERVER_FINISH, ERR_R_INTERNAL_ERROR);
            return -1;
        }
        memcpy(p, s->session->session_id,
               (unsigned int)s->session->session_id_length);
        /* p+=s->session->session_id_length; */

        s->state = SSL2_ST_SEND_SERVER_FINISHED_B;
        s->init_num = s->session->session_id_length + 1;
        s->init_off = 0;
    }

    /* SSL2_ST_SEND_SERVER_FINISHED_B */
    return (ssl2_do_write(s));
}
