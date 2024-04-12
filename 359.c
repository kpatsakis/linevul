static int StreamTcpPacketStateFinWait1(ThreadVars *tv, Packet *p,
                        StreamTcpThread *stt, TcpSession *ssn, PacketQueue *pq)
{
    if (ssn == NULL)
        return -1;

    if (p->tcph->th_flags & TH_RST) {
        if (!StreamTcpValidateRst(ssn, p))
            return -1;

        StreamTcpPacketSetState(p, ssn, TCP_CLOSED);
        SCLogDebug("ssn %p: Reset received state changed to TCP_CLOSED",
                ssn);

        if (PKT_IS_TOSERVER(p)) {
            if ((p->tcph->th_flags & TH_ACK) && StreamTcpValidateAck(ssn, &ssn->server, p) == 0)
                StreamTcpUpdateLastAck(ssn, &ssn->server,
                        StreamTcpResetGetMaxAck(&ssn->server, TCP_GET_ACK(p)));

            StreamTcpUpdateLastAck(ssn, &ssn->client,
                    StreamTcpResetGetMaxAck(&ssn->client, TCP_GET_SEQ(p)));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->client, p, pq);
        } else {
            if ((p->tcph->th_flags & TH_ACK) && StreamTcpValidateAck(ssn, &ssn->client, p) == 0)
                StreamTcpUpdateLastAck(ssn, &ssn->client,
                        StreamTcpResetGetMaxAck(&ssn->client, TCP_GET_ACK(p)));

            StreamTcpUpdateLastAck(ssn, &ssn->server,
                    StreamTcpResetGetMaxAck(&ssn->server, TCP_GET_SEQ(p)));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->server, p, pq);
        }

    } else if ((p->tcph->th_flags & (TH_FIN|TH_ACK)) == (TH_FIN|TH_ACK)) {
        if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
            if (!StreamTcpValidateTimestamp(ssn, p))
                return -1;
        }

        if (PKT_IS_TOSERVER(p)) {
            SCLogDebug("ssn %p: pkt (%" PRIu32 ") is to server: SEQ "
                    "%" PRIu32 ", ACK %" PRIu32 "", ssn, p->payload_len,
                    TCP_GET_SEQ(p), TCP_GET_ACK(p));
            int retransmission = 0;

            if (StreamTcpPacketIsRetransmission(&ssn->client, p)) {
                SCLogDebug("ssn %p: packet is retransmission", ssn);
                retransmission = 1;

            } else if (SEQ_LT(TCP_GET_SEQ(p), ssn->client.next_seq) ||
                    SEQ_GT(TCP_GET_SEQ(p), (ssn->client.last_ack + ssn->client.window)))
            {
                SCLogDebug("ssn %p: -> SEQ mismatch, packet SEQ %" PRIu32 ""
                        " != %" PRIu32 " from stream", ssn,
                        TCP_GET_SEQ(p), ssn->client.next_seq);
                StreamTcpSetEvent(p, STREAM_FIN1_FIN_WRONG_SEQ);
                return -1;
            }

            if (StreamTcpValidateAck(ssn, &ssn->server, p) == -1) {
                SCLogDebug("ssn %p: rejecting because of invalid ack value", ssn);
                StreamTcpSetEvent(p, STREAM_FIN1_INVALID_ACK);
                return -1;
            }

            if (!retransmission) {
                StreamTcpPacketSetState(p, ssn, TCP_TIME_WAIT);
                SCLogDebug("ssn %p: state changed to TCP_TIME_WAIT", ssn);

                ssn->server.window = TCP_GET_WINDOW(p) << ssn->server.wscale;
            }

            StreamTcpUpdateLastAck(ssn, &ssn->server, TCP_GET_ACK(p));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            /* Update the next_seq, in case if we have missed the client
               packet and server has already received and acked it */
            if (SEQ_LT(ssn->server.next_seq, TCP_GET_ACK(p)))
                ssn->server.next_seq = TCP_GET_ACK(p);

            if (SEQ_EQ(ssn->client.next_seq, TCP_GET_SEQ(p))) {
                StreamTcpUpdateNextSeq(ssn, &ssn->client, (ssn->client.next_seq + p->payload_len));
            }

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->client, p, pq);

            SCLogDebug("ssn %p: =+ next SEQ %" PRIu32 ", last ACK "
                    "%" PRIu32 "", ssn, ssn->client.next_seq,
                    ssn->server.last_ack);
        } else { /* implied to client */
            SCLogDebug("ssn %p: pkt (%" PRIu32 ") is to client: SEQ "
                    "%" PRIu32 ", ACK %" PRIu32 "", ssn, p->payload_len,
                    TCP_GET_SEQ(p), TCP_GET_ACK(p));
            int retransmission = 0;

            if (StreamTcpPacketIsRetransmission(&ssn->server, p)) {
                SCLogDebug("ssn %p: packet is retransmission", ssn);
                retransmission = 1;

            } else if (SEQ_LT(TCP_GET_SEQ(p), ssn->server.next_seq) ||
                    SEQ_GT(TCP_GET_SEQ(p), (ssn->server.last_ack + ssn->server.window)))
            {
                SCLogDebug("ssn %p: -> SEQ mismatch, packet SEQ %" PRIu32 ""
                        " != %" PRIu32 " from stream", ssn,
                        TCP_GET_SEQ(p), ssn->server.next_seq);
                StreamTcpSetEvent(p, STREAM_FIN1_FIN_WRONG_SEQ);
                return -1;
            }

            if (StreamTcpValidateAck(ssn, &ssn->client, p) == -1) {
                SCLogDebug("ssn %p: rejecting because of invalid ack value", ssn);
                StreamTcpSetEvent(p, STREAM_FIN1_INVALID_ACK);
                return -1;
            }

            if (!retransmission) {
                StreamTcpPacketSetState(p, ssn, TCP_TIME_WAIT);
                SCLogDebug("ssn %p: state changed to TCP_TIME_WAIT", ssn);

                ssn->client.window = TCP_GET_WINDOW(p) << ssn->client.wscale;
            }

            StreamTcpUpdateLastAck(ssn, &ssn->client, TCP_GET_ACK(p));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            /* Update the next_seq, in case if we have missed the client
               packet and server has already received and acked it */
            if (SEQ_LT(ssn->client.next_seq, TCP_GET_ACK(p)))
                ssn->client.next_seq = TCP_GET_ACK(p);

            if (SEQ_EQ(ssn->server.next_seq, TCP_GET_SEQ(p))) {
                StreamTcpUpdateNextSeq(ssn, &ssn->server, (ssn->server.next_seq + p->payload_len));
            }

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->server, p, pq);

            SCLogDebug("ssn %p: =+ next SEQ %" PRIu32 ", last ACK "
                    "%" PRIu32 "", ssn, ssn->server.next_seq,
                    ssn->client.last_ack);
        }

    } else if (p->tcph->th_flags & TH_FIN) {
        if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
            if (!StreamTcpValidateTimestamp(ssn, p))
                return -1;
        }

        if (PKT_IS_TOSERVER(p)) {
            SCLogDebug("ssn %p: pkt (%" PRIu32 ") is to server: SEQ "
                    "%" PRIu32 ", ACK %" PRIu32 "", ssn, p->payload_len,
                    TCP_GET_SEQ(p), TCP_GET_ACK(p));
            int retransmission = 0;

            if (StreamTcpPacketIsRetransmission(&ssn->client, p)) {
                SCLogDebug("ssn %p: packet is retransmission", ssn);
                retransmission = 1;

            } else if (SEQ_LT(TCP_GET_SEQ(p), ssn->client.next_seq) ||
                    SEQ_GT(TCP_GET_SEQ(p), (ssn->client.last_ack + ssn->client.window)))
            {
                SCLogDebug("ssn %p: -> SEQ mismatch, packet SEQ %" PRIu32 ""
                        " != %" PRIu32 " from stream", ssn,
                        TCP_GET_SEQ(p), ssn->client.next_seq);
                StreamTcpSetEvent(p, STREAM_FIN1_FIN_WRONG_SEQ);
                return -1;
            }

            if (StreamTcpValidateAck(ssn, &ssn->server, p) == -1) {
                SCLogDebug("ssn %p: rejecting because of invalid ack value", ssn);
                StreamTcpSetEvent(p, STREAM_FIN1_INVALID_ACK);
                return -1;
            }

            if (!retransmission) {
                StreamTcpPacketSetState(p, ssn, TCP_CLOSING);
                SCLogDebug("ssn %p: state changed to TCP_CLOSING", ssn);

                ssn->server.window = TCP_GET_WINDOW(p) << ssn->server.wscale;
            }

            StreamTcpUpdateLastAck(ssn, &ssn->server, TCP_GET_ACK(p));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            /* Update the next_seq, in case if we have missed the client
               packet and server has already received and acked it */
            if (SEQ_LT(ssn->server.next_seq, TCP_GET_ACK(p)))
                ssn->server.next_seq = TCP_GET_ACK(p);

            if (SEQ_EQ(ssn->client.next_seq, TCP_GET_SEQ(p))) {
                StreamTcpUpdateNextSeq(ssn, &ssn->client, (ssn->client.next_seq + p->payload_len));
            }

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->client, p, pq);

            SCLogDebug("ssn %p: =+ next SEQ %" PRIu32 ", last ACK "
                    "%" PRIu32 "", ssn, ssn->client.next_seq,
                    ssn->server.last_ack);
        } else { /* implied to client */
            SCLogDebug("ssn %p: pkt (%" PRIu32 ") is to client: SEQ "
                    "%" PRIu32 ", ACK %" PRIu32 "", ssn, p->payload_len,
                    TCP_GET_SEQ(p), TCP_GET_ACK(p));

            int retransmission = 0;

            if (StreamTcpPacketIsRetransmission(&ssn->server, p)) {
                SCLogDebug("ssn %p: packet is retransmission", ssn);
                retransmission = 1;

            } else if (SEQ_LT(TCP_GET_SEQ(p), ssn->server.next_seq) ||
                    SEQ_GT(TCP_GET_SEQ(p), (ssn->server.last_ack + ssn->server.window)))
            {
                SCLogDebug("ssn %p: -> SEQ mismatch, packet SEQ %" PRIu32 ""
                        " != %" PRIu32 " from stream", ssn,
                        TCP_GET_SEQ(p), ssn->server.next_seq);
                StreamTcpSetEvent(p, STREAM_FIN1_FIN_WRONG_SEQ);
                return -1;
            }

            if (StreamTcpValidateAck(ssn, &ssn->client, p) == -1) {
                SCLogDebug("ssn %p: rejecting because of invalid ack value", ssn);
                StreamTcpSetEvent(p, STREAM_FIN1_INVALID_ACK);
                return -1;
            }

            if (!retransmission) {
                StreamTcpPacketSetState(p, ssn, TCP_CLOSING);
                SCLogDebug("ssn %p: state changed to TCP_CLOSING", ssn);

                ssn->client.window = TCP_GET_WINDOW(p) << ssn->client.wscale;
            }

            StreamTcpUpdateLastAck(ssn, &ssn->client, TCP_GET_ACK(p));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            /* Update the next_seq, in case if we have missed the client
               packet and server has already received and acked it */
            if (SEQ_LT(ssn->client.next_seq, TCP_GET_ACK(p)))
                ssn->client.next_seq = TCP_GET_ACK(p);

            if (SEQ_EQ(ssn->server.next_seq, TCP_GET_SEQ(p))) {
                StreamTcpUpdateNextSeq(ssn, &ssn->server, (ssn->server.next_seq + p->payload_len));
            }

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->server, p, pq);

            SCLogDebug("ssn %p: =+ next SEQ %" PRIu32 ", last ACK "
                    "%" PRIu32 "", ssn, ssn->server.next_seq,
                    ssn->client.last_ack);
        }
    } else if (p->tcph->th_flags & TH_SYN) {
        SCLogDebug("ssn (%p): SYN pkt on FinWait1", ssn);
        StreamTcpSetEvent(p, STREAM_SHUTDOWN_SYN_RESEND);
        return -1;

    } else if (p->tcph->th_flags & TH_ACK) {
        if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
            if (!StreamTcpValidateTimestamp(ssn, p))
                return -1;
        }

        if (PKT_IS_TOSERVER(p)) {
            SCLogDebug("ssn %p: pkt (%" PRIu32 ") is to server: SEQ "
                    "%" PRIu32 ", ACK %" PRIu32 "", ssn, p->payload_len,
                    TCP_GET_SEQ(p), TCP_GET_ACK(p));
            int retransmission = 0;

            if (StreamTcpPacketIsRetransmission(&ssn->client, p)) {
                SCLogDebug("ssn %p: packet is retransmission", ssn);
                retransmission = 1;
            }

            if (StreamTcpValidateAck(ssn, &ssn->server, p) == -1) {
                SCLogDebug("ssn %p: rejecting because of invalid ack value", ssn);
                StreamTcpSetEvent(p, STREAM_FIN1_INVALID_ACK);
                return -1;
            }

            if (!retransmission) {
                if (SEQ_LEQ(TCP_GET_SEQ(p) + p->payload_len, ssn->client.next_win) ||
                        (ssn->flags & (STREAMTCP_FLAG_MIDSTREAM|STREAMTCP_FLAG_ASYNC)))
                {
                    SCLogDebug("ssn %p: seq %"PRIu32" in window, ssn->client.next_win "
                            "%" PRIu32 "", ssn, TCP_GET_SEQ(p), ssn->client.next_win);

                    if (TCP_GET_SEQ(p) == ssn->client.next_seq) {
                        StreamTcpPacketSetState(p, ssn, TCP_FIN_WAIT2);
                        SCLogDebug("ssn %p: state changed to TCP_FIN_WAIT2", ssn);
                    }
                } else {
                    SCLogDebug("ssn %p: -> SEQ mismatch, packet SEQ %" PRIu32 ""
                            " != %" PRIu32 " from stream", ssn,
                            TCP_GET_SEQ(p), ssn->client.next_seq);

                    StreamTcpSetEvent(p, STREAM_FIN1_ACK_WRONG_SEQ);
                    return -1;
                }

                ssn->server.window = TCP_GET_WINDOW(p) << ssn->server.wscale;
            }

            StreamTcpUpdateLastAck(ssn, &ssn->server, TCP_GET_ACK(p));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            /* Update the next_seq, in case if we have missed the client
               packet and server has already received and acked it */
            if (SEQ_LT(ssn->server.next_seq, TCP_GET_ACK(p)))
                ssn->server.next_seq = TCP_GET_ACK(p);

            if (SEQ_EQ(ssn->client.next_seq, TCP_GET_SEQ(p))) {
                StreamTcpUpdateNextSeq(ssn, &ssn->client, (ssn->client.next_seq + p->payload_len));
            }

            StreamTcpSackUpdatePacket(&ssn->server, p);

            /* update next_win */
            StreamTcpUpdateNextWin(ssn, &ssn->server, (ssn->server.last_ack + ssn->server.window));

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->client, p, pq);

            SCLogDebug("ssn %p: =+ next SEQ %" PRIu32 ", last ACK "
                    "%" PRIu32 "", ssn, ssn->client.next_seq,
                    ssn->server.last_ack);

        } else { /* implied to client */

            SCLogDebug("ssn %p: pkt (%" PRIu32 ") is to client: SEQ "
                    "%" PRIu32 ", ACK %" PRIu32 "", ssn, p->payload_len,
                    TCP_GET_SEQ(p), TCP_GET_ACK(p));

            int retransmission = 0;

            if (StreamTcpPacketIsRetransmission(&ssn->server, p)) {
                SCLogDebug("ssn %p: packet is retransmission", ssn);
                retransmission = 1;
            }

            if (StreamTcpValidateAck(ssn, &ssn->client, p) == -1) {
                SCLogDebug("ssn %p: rejecting because of invalid ack value", ssn);
                StreamTcpSetEvent(p, STREAM_FIN1_INVALID_ACK);
                return -1;
            }

            if (!retransmission) {
                if (SEQ_LEQ(TCP_GET_SEQ(p) + p->payload_len, ssn->server.next_win) ||
                        (ssn->flags & (STREAMTCP_FLAG_MIDSTREAM|STREAMTCP_FLAG_ASYNC)))
                {
                    SCLogDebug("ssn %p: seq %"PRIu32" in window, ssn->server.next_win "
                            "%" PRIu32 "", ssn, TCP_GET_SEQ(p), ssn->server.next_win);

                    if (TCP_GET_SEQ(p) == ssn->server.next_seq) {
                        StreamTcpPacketSetState(p, ssn, TCP_FIN_WAIT2);
                        SCLogDebug("ssn %p: state changed to TCP_FIN_WAIT2", ssn);
                    }
                } else {
                    SCLogDebug("ssn %p: -> SEQ mismatch, packet SEQ %" PRIu32 ""
                            " != %" PRIu32 " from stream", ssn,
                            TCP_GET_SEQ(p), ssn->server.next_seq);
                    StreamTcpSetEvent(p, STREAM_FIN1_ACK_WRONG_SEQ);
                    return -1;
                }

                ssn->client.window = TCP_GET_WINDOW(p) << ssn->client.wscale;
            }

            StreamTcpUpdateLastAck(ssn, &ssn->client, TCP_GET_ACK(p));

            if (ssn->flags & STREAMTCP_FLAG_TIMESTAMP) {
                StreamTcpHandleTimestamp(ssn, p);
            }

            /* Update the next_seq, in case if we have missed the client
               packet and server has already received and acked it */
            if (SEQ_LT(ssn->client.next_seq, TCP_GET_ACK(p)))
                ssn->client.next_seq = TCP_GET_ACK(p);

            if (SEQ_EQ(ssn->server.next_seq, TCP_GET_SEQ(p))) {
                StreamTcpUpdateNextSeq(ssn, &ssn->server, (ssn->server.next_seq + p->payload_len));
            }

            StreamTcpSackUpdatePacket(&ssn->client, p);

            /* update next_win */
            StreamTcpUpdateNextWin(ssn, &ssn->client, (ssn->client.last_ack + ssn->client.window));

            StreamTcpReassembleHandleSegment(tv, stt->ra_ctx, ssn,
                    &ssn->server, p, pq);

            SCLogDebug("ssn %p: =+ next SEQ %" PRIu32 ", last ACK "
                    "%" PRIu32 "", ssn, ssn->server.next_seq,
                    ssn->client.last_ack);
        }
    } else {
        SCLogDebug("ssn (%p): default case", ssn);
    }

    return 0;
}
