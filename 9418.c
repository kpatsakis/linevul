static TcpSession *StreamTcpNewSession (Packet *p, int id)
{
    TcpSession *ssn = (TcpSession *)p->flow->protoctx;

    if (ssn == NULL) {
        p->flow->protoctx = PoolThreadGetById(ssn_pool, id);
#ifdef DEBUG
        SCMutexLock(&ssn_pool_mutex);
        if (p->flow->protoctx != NULL)
            ssn_pool_cnt++;
        SCMutexUnlock(&ssn_pool_mutex);
#endif

        ssn = (TcpSession *)p->flow->protoctx;
        if (ssn == NULL) {
            SCLogDebug("ssn_pool is empty");
            return NULL;
        }

        ssn->state = TCP_NONE;
        ssn->reassembly_depth = stream_config.reassembly_depth;
        ssn->tcp_packet_flags = p->tcph ? p->tcph->th_flags : 0;
        ssn->server.flags = stream_config.stream_init_flags;
        ssn->client.flags = stream_config.stream_init_flags;

        StreamingBuffer x = STREAMING_BUFFER_INITIALIZER(&stream_config.sbcnf);
        ssn->client.sb = x;
        ssn->server.sb = x;

        if (PKT_IS_TOSERVER(p)) {
            ssn->client.tcp_flags = p->tcph ? p->tcph->th_flags : 0;
            ssn->server.tcp_flags = 0;
        } else if (PKT_IS_TOCLIENT(p)) {
            ssn->server.tcp_flags = p->tcph ? p->tcph->th_flags : 0;
            ssn->client.tcp_flags = 0;
        }
    }

    return ssn;
}
