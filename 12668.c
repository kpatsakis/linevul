long get_user_pages_remote(struct task_struct *tsk, struct mm_struct *mm,
		unsigned long start, unsigned long nr_pages,
		int write, int force, struct page **pages,
		struct vm_area_struct **vmas)
{
	return __get_user_pages_locked(tsk, mm, start, nr_pages, write, force,
				       pages, vmas, NULL, false,
				       FOLL_TOUCH | FOLL_REMOTE);
}
