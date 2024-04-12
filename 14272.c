static int StreamTcpTest37(void)
{
    Packet *p = SCMalloc(SIZE_OF_PACKET);
    if (unlikely(p == NULL))
        return 0;
    Flow f;
    ThreadVars tv;
    StreamTcpThread stt;
    uint8_t payload[4];
    TCPHdr tcph;
    int ret = 0;
    PacketQueue pq;
    memset(&pq,0,sizeof(PacketQueue));

    memset(p, 0, SIZE_OF_PACKET);
    memset (&f, 0, sizeof(Flow));
    memset(&tv, 0, sizeof (ThreadVars));
    memset(&stt, 0, sizeof (StreamTcpThread));
    memset(&tcph, 0, sizeof (TCPHdr));

    FLOW_INITIALIZE(&f);

    p->flow = &f;
    tcph.th_win = htons(5480);
    tcph.th_flags = TH_SYN;
    p->tcph = &tcph;
    p->flowflags = FLOW_PKT_TOSERVER;

    StreamTcpUTInit(&stt.ra_ctx);

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1) {
        printf("failed in processing packet\n");
        goto end;
    }

    p->tcph->th_ack = htonl(1);
    p->tcph->th_flags = TH_SYN | TH_ACK;
    p->flowflags = FLOW_PKT_TOCLIENT;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1 || (TcpSession *)p->flow->protoctx == NULL) {
        printf("failed in processing packet\n");
        goto end;
    }

    p->tcph->th_ack = htonl(1);
    p->tcph->th_seq = htonl(1);
    p->tcph->th_flags = TH_ACK;
    p->flowflags = FLOW_PKT_TOSERVER;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1 || (TcpSession *)p->flow->protoctx == NULL) {
        printf("failed in processing packet\n");
        goto end;
    }

    if (((TcpSession *)p->flow->protoctx)->state != TCP_ESTABLISHED) {
        printf("the TCP state should be TCP_ESTABLISEHD\n");
        goto end;
    }

    p->tcph->th_ack = htonl(2);
    p->tcph->th_seq = htonl(4);
    p->tcph->th_flags = TH_ACK|TH_FIN;
    p->flowflags = FLOW_PKT_TOSERVER;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1 || (TcpSession *)p->flow->protoctx == NULL) {
        printf("failed in processing packet\n");
        goto end;
    }

    if (((TcpSession *)p->flow->protoctx)->state != TCP_CLOSE_WAIT) {
        printf("the TCP state should be TCP_CLOSE_WAIT\n");
        goto end;
    }

    p->tcph->th_ack = htonl(1);
    p->tcph->th_seq = htonl(1);
    p->tcph->th_flags = TH_PUSH | TH_ACK;
    p->flowflags = FLOW_PKT_TOSERVER;

    StreamTcpCreateTestPacket(payload, 0x41, 3, 4); /*AAA*/
    p->payload = payload;
    p->payload_len = 3;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1 || (TcpSession *)p->flow->protoctx == NULL) {
        printf("failed in processing packet\n");
        goto end;
    }

    p->tcph->th_ack = htonl(4);
    p->tcph->th_seq = htonl(2);
    p->tcph->th_flags = TH_ACK;
    p->payload_len = 0;
    p->flowflags = FLOW_PKT_TOCLIENT;

    if (StreamTcpPacket(&tv, p, &stt, &pq) == -1 || (TcpSession *)p->flow->protoctx == NULL) {
        printf("failed in processing packet\n");
        goto end;
    }

    TcpStream *stream = &(((TcpSession *)p->flow->protoctx)->client);
    FAIL_IF(STREAM_RAW_PROGRESS(stream) != 0); // no detect no progress update

    StreamTcpSessionClear(p->flow->protoctx);

    ret = 1;
end:
    SCFree(p);
    FLOW_DESTROY(&f);
    StreamTcpUTDeinit(stt.ra_ctx);
    return ret;
}
