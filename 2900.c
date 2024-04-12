static int global_template_search(const char *key, void *data, void *privdata)
{
	template_iter_t *iter = privdata;
	default_template_t *def_t = data;

	if (def_t->flags == iter->level)
		iter->res = key;

	return 0;
}
