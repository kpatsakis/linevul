static void ssh_pkt_addbyte(struct Packet *pkt, unsigned char byte)
{
    ssh_pkt_adddata(pkt, &byte, 1);
}
