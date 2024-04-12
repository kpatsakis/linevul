ofputil_decode_port_stats(struct ofputil_port_stats *ps, struct ofpbuf *msg)
{
    enum ofperr error;
    enum ofpraw raw;

    memset(&(ps->stats), 0xFF, sizeof (ps->stats));

    error = (msg->header ? ofpraw_decode(&raw, msg->header)
             : ofpraw_pull(&raw, msg));
    if (error) {
        return error;
    }

    if (!msg->size) {
        return EOF;
    } else if (raw == OFPRAW_OFPST14_PORT_REPLY) {
        return ofputil_pull_ofp14_port_stats(ps, msg);
    } else if (raw == OFPRAW_OFPST13_PORT_REPLY) {
        const struct ofp13_port_stats *ps13;
        ps13 = ofpbuf_try_pull(msg, sizeof *ps13);
        if (!ps13) {
            goto bad_len;
        }
        return ofputil_port_stats_from_ofp13(ps, ps13);
    } else if (raw == OFPRAW_OFPST11_PORT_REPLY) {
        const struct ofp11_port_stats *ps11;

        ps11 = ofpbuf_try_pull(msg, sizeof *ps11);
        if (!ps11) {
            goto bad_len;
        }
        return ofputil_port_stats_from_ofp11(ps, ps11);
    } else if (raw == OFPRAW_OFPST10_PORT_REPLY) {
        const struct ofp10_port_stats *ps10;

        ps10 = ofpbuf_try_pull(msg, sizeof *ps10);
        if (!ps10) {
            goto bad_len;
        }
        return ofputil_port_stats_from_ofp10(ps, ps10);
    } else {
        OVS_NOT_REACHED();
    }

 bad_len:
    VLOG_WARN_RL(&bad_ofmsg_rl, "OFPST_PORT reply has %"PRIu32" leftover "
                 "bytes at end", msg->size);
    return OFPERR_OFPBRC_BAD_LEN;
}
