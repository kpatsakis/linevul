encode_fh(__be32 *p, struct svc_fh *fhp)
{
	unsigned int size = fhp->fh_handle.fh_size;
	*p++ = htonl(size);
	if (size) p[XDR_QUADLEN(size)-1]=0;
	memcpy(p, &fhp->fh_handle.fh_base, size);
	return p + XDR_QUADLEN(size);
}
