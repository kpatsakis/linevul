static int ssh1_pkt_getrsakey(struct Packet *pkt, struct RSAKey *key,
			      const unsigned char **keystr)
{
    int j;

    j = makekey(pkt->body + pkt->savedpos,
		pkt->length - pkt->savedpos,
		key, keystr, 0);

    if (j < 0)
	return FALSE;
    
    pkt->savedpos += j;
    assert(pkt->savedpos < pkt->length);

    return TRUE;
}
