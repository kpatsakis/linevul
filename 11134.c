static TcpStateQueue *StreamTcp3whsFindSynAckBySynAck(TcpSession *ssn, Packet *p)
{
    TcpStateQueue *q = ssn->queue;
    TcpStateQueue search;

    StreamTcp3whsSynAckToStateQueue(p, &search);

    while (q != NULL) {
        if (search.flags == q->flags &&
            search.wscale == q->wscale &&
            search.win == q->win &&
            search.seq == q->seq &&
            search.ack == q->ack &&
            search.ts == q->ts) {
            return q;
        }

        q = q->next;
    }

    return q;
}
