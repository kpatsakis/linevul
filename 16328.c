int lh_table_insert(struct lh_table *t, void *k, const void *v)
{
	unsigned long h, n;

	t->inserts++;
	if(t->count >= t->size * LH_LOAD_FACTOR) lh_table_resize(t, t->size * 2);

	h = t->hash_fn(k);
	n = h % t->size;

	while( 1 ) {
		if(t->table[n].k == LH_EMPTY || t->table[n].k == LH_FREED) break;
		t->collisions++;
		if ((int)++n == t->size) n = 0;
	}

	t->table[n].k = k;
	t->table[n].v = v;
	t->count++;

	if(t->head == NULL) {
		t->head = t->tail = &t->table[n];
		t->table[n].next = t->table[n].prev = NULL;
	} else {
		t->tail->next = &t->table[n];
		t->table[n].prev = t->tail;
		t->table[n].next = NULL;
		t->tail = &t->table[n];
	}

	return 0;
}
