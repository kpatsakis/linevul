static void mpol_set_task_struct_flag(void)
{
	mpol_fix_fork_child_flag(current);
}
