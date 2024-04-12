NORET_TYPE void complete_and_exit(struct completion *comp, long code)
{
	if (comp)
		complete(comp);

	do_exit(code);
}
