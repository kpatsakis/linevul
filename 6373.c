getname(const char __user * filename)
{
	return getname_flags(filename, 0, NULL);
}