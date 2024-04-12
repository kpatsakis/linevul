int fpm_stdio_discard_pipes(struct fpm_child_s *child) /* {{{ */
{
	if (0 == child->wp->config->catch_workers_output) { /* not required */
		return 0;
	}

	close(fd_stdout[1]);
	close(fd_stderr[1]);

	close(fd_stdout[0]);
	close(fd_stderr[0]);
	return 0;
}
/* }}} */
