check_lock_length(u64 offset, u64 length)
{
	return ((length == 0) || ((length != NFS4_MAX_UINT64) &&
		(length > ~offset)));
}
