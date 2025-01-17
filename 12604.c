static int ceph_x_encrypt(struct ceph_crypto_key *secret,
			  void *ibuf, int ilen, void *obuf, size_t olen)
{
	struct ceph_x_encrypt_header head = {
		.struct_v = 1,
		.magic = cpu_to_le64(CEPHX_ENC_MAGIC)
	};
	size_t len = olen - sizeof(u32);
	int ret;

	ret = ceph_encrypt2(secret, obuf + sizeof(u32), &len,
			    &head, sizeof(head), ibuf, ilen);
	if (ret)
		return ret;
	ceph_encode_32(&obuf, len);
	return len + sizeof(u32);
 }
