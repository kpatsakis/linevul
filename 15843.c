__find_swevent_head(struct swevent_hlist *hlist, u64 type, u32 event_id)
{
	u64 hash = swevent_hash(type, event_id);

	return &hlist->heads[hash];
}
