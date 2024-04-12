void mem_cgroup_print_bad_page(struct page *page)
{
	struct page_cgroup *pc;

	pc = lookup_page_cgroup_used(page);
	if (pc) {
		printk(KERN_ALERT "pc:%p pc->flags:%lx pc->mem_cgroup:%p\n",
		       pc, pc->flags, pc->mem_cgroup);
	}
}
