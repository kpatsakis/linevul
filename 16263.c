static int ssh_channelcmp(void *av, void *bv)
{
    struct ssh_channel *a = (struct ssh_channel *) av;
    struct ssh_channel *b = (struct ssh_channel *) bv;
    if (a->localid < b->localid)
	return -1;
    if (a->localid > b->localid)
	return +1;
    return 0;
}
