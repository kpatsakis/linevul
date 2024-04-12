 static void fpm_child_init(struct fpm_worker_pool_s *wp) /* {{{ */
 {
 	fpm_globals.max_requests = wp->config->pm_max_requests;
 
 	if (0 > fpm_stdio_init_child(wp)  ||
 	    0 > fpm_log_init_child(wp)    ||
	    0 > fpm_status_init_child(wp) ||
	    0 > fpm_unix_init_child(wp)   ||
	    0 > fpm_signals_init_child()  ||
	    0 > fpm_env_init_child(wp)    ||
	    0 > fpm_php_init_child(wp)) {

		zlog(ZLOG_ERROR, "[pool %s] child failed to initialize", wp->config->name);
		exit(FPM_EXIT_SOFTWARE);
	}
}
/* }}} */
