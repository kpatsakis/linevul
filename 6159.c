check_notify_script_secure(notify_script_t **script_p, magic_t magic)
{
	int flags;
	notify_script_t *script = *script_p;

	if (!script)
		return 0;

	flags = check_script_secure(script, magic);

	/* Mark not to run if needs inhibiting */
	if ((flags & (SC_INHIBIT | SC_NOTFOUND)) ||
	    !(flags & SC_EXECUTABLE))
		free_notify_script(script_p);

	return flags;
}
