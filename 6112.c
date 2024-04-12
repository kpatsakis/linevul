static int __init user_debug_setup(char *str)
{
	get_option(&str, &user_debug);
	return 1;
}
