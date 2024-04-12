static void fill_user_desc(struct user_desc *info, int idx,
			   const struct desc_struct *desc)

{
	memset(info, 0, sizeof(*info));
	info->entry_number = idx;
	info->base_addr = get_desc_base(desc);
	info->limit = get_desc_limit(desc);
	info->seg_32bit = desc->d;
	info->contents = desc->type >> 2;
	info->read_exec_only = !(desc->type & 2);
	info->limit_in_pages = desc->g;
	info->seg_not_present = !desc->p;
	info->useable = desc->avl;
#ifdef CONFIG_X86_64
	info->lm = desc->l;
#endif
}
