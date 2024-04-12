R_API bool r_flag_exist_at(RFlag *f, const char *flag_prefix, ut16 fp_size, ut64 off) {
	RListIter *iter = NULL;
	RFlagItem *item = NULL;
	if (!f) {
		return false;
	}
	const RList *list = r_flag_get_list (f, off);
	if (!list) {
		return false;
	}
	r_list_foreach (list, iter, item) {
		if (item->name && !strncmp (item->name, flag_prefix, fp_size)) {
			return true;
		}
	}
	return false;
}
