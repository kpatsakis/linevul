nfsd4_decode_bitmap(struct nfsd4_compoundargs *argp, u32 *bmval)
{
	u32 bmlen;
	DECODE_HEAD;

	bmval[0] = 0;
	bmval[1] = 0;
	bmval[2] = 0;

	READ_BUF(4);
	bmlen = be32_to_cpup(p++);
	if (bmlen > 1000)
		goto xdr_error;

	READ_BUF(bmlen << 2);
	if (bmlen > 0)
		bmval[0] = be32_to_cpup(p++);
	if (bmlen > 1)
		bmval[1] = be32_to_cpup(p++);
	if (bmlen > 2)
		bmval[2] = be32_to_cpup(p++);

	DECODE_TAIL;
}
