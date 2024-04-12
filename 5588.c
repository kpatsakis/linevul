TEE_Result syscall_cipher_update(unsigned long state, const void *src,
			size_t src_len, void *dst, uint64_t *dst_len)
{
	return tee_svc_cipher_update_helper(state, false /* last_block */,
					    src, src_len, dst, dst_len);
}
