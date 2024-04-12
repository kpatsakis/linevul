void __readwrite_bug(const char *fn)
{
	printk("%s called, but not implemented\n", fn);
	BUG();
}
