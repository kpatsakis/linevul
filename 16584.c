int git_index__changed_relative_to(
	git_index *index, const git_oid *checksum)
{
	/* attempt to update index (ignoring errors) */
	if (git_index_read(index, false) < 0)
		giterr_clear();

	return !!git_oid_cmp(&index->checksum, checksum);
}
