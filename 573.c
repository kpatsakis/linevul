int TcpSessionPacketSsnReuse(const Packet *p, const Flow *f, const void *tcp_ssn)
{
    if (p->proto == IPPROTO_TCP && p->tcph != NULL) {
        if (TcpSessionPacketIsStreamStarter(p) == 1) {
            if (TcpSessionReuseDoneEnough(p, f, tcp_ssn) == 1) {
                return 1;
            }
        }
    }
    return 0;
}
