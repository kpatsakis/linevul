static int StreamTcpTest39 (void)
{
    Flow f;
    ThreadVars tv;
    StreamTcpThread stt;
    uint8_t payload[4];
    TCPHdr tcph;
    PacketQueue pq;

    memset (&f, 0, sizeof(Flow));
    memset(&tv, 0, sizeof (ThreadVars));
    memset(&stt, 0, sizeof (StreamTcpThread));
    memset(&tcph, 0, sizeof (TCPHdr));
    memset(&pq,0,sizeof(PacketQueue));

    Packet *p = SCMalloc(SIZE_OF_PACKET);
    if (unlikely(p == NULL))
        return 0;
    memset(p, 0, SIZE_OF_PACKET);

    FLOW_INITIALIZE(&f);
    p->flow = &f;
    tcph.th_win = htons(5480);
    tcph.th_flags = TH_SYN;
    p->tcph = &tcph;
    p->flowflags = FLOW_PKT_TOSERVER;
    int ret = 0;

    StreamTcpUTInit(&stt.ra_ctx);

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet in StreamTcpPacket\n");
        goto end;
    }

    p->tcph->th_ack = htonl(1);
    p->tcph->th_flags = TH_SYN | TH_ACK;
    p->flowflags = FLOW_PKT_TOCLIENT;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet in StreamTcpPacket\n");
        goto end;
    }

    p->tcph->th_ack = htonl(1);
    p->tcph->th_seq = htonl(1);
    p->tcph->th_flags = TH_ACK;
    p->flowflags = FLOW_PKT_TOSERVER;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet in StreamTcpPacket\n");
        goto end;
    }

    p->tcph->th_ack = htonl(1);
    p->tcph->th_seq = htonl(1);
    p->tcph->th_flags = TH_PUSH | TH_ACK;
    p->flowflags = FLOW_PKT_TOCLIENT;

    StreamTcpCreateTestPacket(payload, 0x41, 3, 4); /*AAA*/
    p->payload = payload;
    p->payload_len = 3;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet in StreamTcpPacket\n");
        goto end;
    }

    if (((TcpSession *)(p->flow->protoctx))->server.next_seq != 4) {
        printf("the server.next_seq should be 4, but it is %"PRIu32"\n",
                ((TcpSession *)(p->flow->protoctx))->server.next_seq);
        goto end;
    }

    p->tcph->th_ack = htonl(4);
    p->tcph->th_seq = htonl(2);
    p->tcph->th_flags = TH_PUSH | TH_ACK;
    p->flowflags = FLOW_PKT_TOSERVER;

    StreamTcpCreateTestPacket(payload, 0x41, 3, 4); /*AAA*/
    p->payload = payload;
    p->payload_len = 3;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet in StreamTcpPacket\n");
        goto end;
    }

    /* last_ack value should be 4 as the previous sent ACK value is inside
       window */
    if (((TcpSession *)(p->flow->protoctx))->server.last_ack != 4) {
        printf("the server.last_ack should be 4, but it is %"PRIu32"\n",
                ((TcpSession *)(p->flow->protoctx))->server.last_ack);
        goto end;
    }

    p->tcph->th_seq = htonl(4);
    p->tcph->th_ack = htonl(5);
    p->tcph->th_flags = TH_PUSH | TH_ACK;
    p->flowflags = FLOW_PKT_TOCLIENT;

    StreamTcpCreateTestPacket(payload, 0x41, 3, 4); /*AAA*/
    p->payload = payload;
    p->payload_len = 3;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet in StreamTcpPacket\n");
        goto end;
    }

    /* next_seq value should be 2987 as the previous sent ACK value is inside
       window */
    if (((TcpSession *)(p->flow->protoctx))->server.next_seq != 7) {
        printf("the server.next_seq should be 7, but it is %"PRIu32"\n",
                ((TcpSession *)(p->flow->protoctx))->server.next_seq);
        goto end;
    }

    ret = 1;

end:
    StreamTcpSessionClear(p->flow->protoctx);
    SCFree(p);
    FLOW_DESTROY(&f);
    StreamTcpUTDeinit(stt.ra_ctx);
    return ret;
}
