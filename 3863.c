static SUB_STATE_RETURN read_state_machine(SSL *s)
{
    OSSL_STATEM *st = &s->statem;
    int ret, mt;
    unsigned long len = 0;
    int (*transition) (SSL *s, int mt);
    PACKET pkt;
    MSG_PROCESS_RETURN(*process_message) (SSL *s, PACKET *pkt);
    WORK_STATE(*post_process_message) (SSL *s, WORK_STATE wst);
    unsigned long (*max_message_size) (SSL *s);
    void (*cb) (const SSL *ssl, int type, int val) = NULL;

    cb = get_callback(s);

    if (s->server) {
        transition = ossl_statem_server_read_transition;
        process_message = ossl_statem_server_process_message;
        max_message_size = ossl_statem_server_max_message_size;
        post_process_message = ossl_statem_server_post_process_message;
    } else {
        transition = ossl_statem_client_read_transition;
        process_message = ossl_statem_client_process_message;
        max_message_size = ossl_statem_client_max_message_size;
        post_process_message = ossl_statem_client_post_process_message;
    }

    if (st->read_state_first_init) {
        s->first_packet = 1;
        st->read_state_first_init = 0;
    }

    while (1) {
        switch (st->read_state) {
        case READ_STATE_HEADER:
            /* Get the state the peer wants to move to */
            if (SSL_IS_DTLS(s)) {
                /*
                 * In DTLS we get the whole message in one go - header and body
                 */
                ret = dtls_get_message(s, &mt, &len);
            } else {
                ret = tls_get_message_header(s, &mt);
            }

            if (ret == 0) {
                /* Could be non-blocking IO */
                return SUB_STATE_ERROR;
            }

            if (cb != NULL) {
                /* Notify callback of an impending state change */
                if (s->server)
                    cb(s, SSL_CB_ACCEPT_LOOP, 1);
                else
                    cb(s, SSL_CB_CONNECT_LOOP, 1);
            }
            /*
             * Validate that we are allowed to move to the new state and move
             * to that state if so
             */
            if (!transition(s, mt)) {
                ossl_statem_set_error(s);
                return SUB_STATE_ERROR;
            }

            if (s->s3->tmp.message_size > max_message_size(s)) {
                ssl3_send_alert(s, SSL3_AL_FATAL, SSL_AD_ILLEGAL_PARAMETER);
                SSLerr(SSL_F_READ_STATE_MACHINE, SSL_R_EXCESSIVE_MESSAGE_SIZE);
                 return SUB_STATE_ERROR;
             }
 
             st->read_state = READ_STATE_BODY;
             /* Fall through */
            if (!PACKET_buf_init(&pkt, s->init_msg, len)) {
                ssl3_send_alert(s, SSL3_AL_FATAL, SSL_AD_INTERNAL_ERROR);
                SSLerr(SSL_F_READ_STATE_MACHINE, ERR_R_INTERNAL_ERROR);
                return SUB_STATE_ERROR;
            }
            ret = process_message(s, &pkt);

            /* Discard the packet data */
            s->init_num = 0;

            switch (ret) {
            case MSG_PROCESS_ERROR:
                return SUB_STATE_ERROR;

            case MSG_PROCESS_FINISHED_READING:
                if (SSL_IS_DTLS(s)) {
                    dtls1_stop_timer(s);
                }
                return SUB_STATE_FINISHED;

            case MSG_PROCESS_CONTINUE_PROCESSING:
                st->read_state = READ_STATE_POST_PROCESS;
                st->read_state_work = WORK_MORE_A;
                break;

            default:
                st->read_state = READ_STATE_HEADER;
                break;
            }
            break;

        case READ_STATE_POST_PROCESS:
            st->read_state_work = post_process_message(s, st->read_state_work);
            switch (st->read_state_work) {
            default:
                return SUB_STATE_ERROR;

            case WORK_FINISHED_CONTINUE:
                st->read_state = READ_STATE_HEADER;
                break;

            case WORK_FINISHED_STOP:
                if (SSL_IS_DTLS(s)) {
                    dtls1_stop_timer(s);
                }
                return SUB_STATE_FINISHED;
            }
            break;

        default:
            /* Shouldn't happen */
            ssl3_send_alert(s, SSL3_AL_FATAL, SSL_AD_INTERNAL_ERROR);
            SSLerr(SSL_F_READ_STATE_MACHINE, ERR_R_INTERNAL_ERROR);
            ossl_statem_set_error(s);
            return SUB_STATE_ERROR;
        }
    }
}
