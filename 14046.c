static void __user *u64_to_ptr(__u64 val)
{
	return (void __user *) (unsigned long) val;
}
