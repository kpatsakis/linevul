struct lh_entry* lh_table_lookup_entry(struct lh_table *t, const void *k)
{
	unsigned long h = t->hash_fn(k);
	unsigned long n = h % t->size;
	int count = 0;

	t->lookups++;
	while( count < t->size ) {
		if(t->table[n].k == LH_EMPTY) return NULL;
		if(t->table[n].k != LH_FREED &&
		   t->equal_fn(t->table[n].k, k)) return &t->table[n];
		if ((int)++n == t->size) n = 0;
		count++;
	}
	return NULL;
}
