free_parent_mallocs_startup(bool am_child)
{
	if (am_child) {
#if HAVE_DECL_CLONE_NEWNET
		free_dirname();
#endif
#ifndef _MEM_CHECK_LOG_
		FREE_PTR(syslog_ident);
#else
		free(syslog_ident);
#endif
		syslog_ident = NULL;

		FREE_PTR(orig_core_dump_pattern);
	}

	if (free_main_pidfile) {
		FREE_PTR(main_pidfile);
		free_main_pidfile = false;
	}
}
