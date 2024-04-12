static void write_exception(struct pstore *ps,
			    uint32_t index, struct core_exception *e)
{
	struct disk_exception *de = get_exception(ps, index);

	/* copy it */
	de->old_chunk = cpu_to_le64(e->old_chunk);
	de->new_chunk = cpu_to_le64(e->new_chunk);
}
