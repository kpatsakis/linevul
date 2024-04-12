void start_application(int no_sandbox, FILE *fp) {
	if (no_sandbox == 0) {
		env_defaults();
		env_apply();
	}
	umask(orig_umask);

	if (arg_debug) {
		printf("starting application\n");
		printf("LD_PRELOAD=%s\n", getenv("LD_PRELOAD"));
	}

	if (arg_audit) {
		assert(arg_audit_prog);

		if (fp) {
			fprintf(fp, "ready\n");
			fclose(fp);
		}
#ifdef HAVE_GCOV
		__gcov_dump();
#endif
#ifdef HAVE_SECCOMP
		seccomp_install_filters();
#endif
		execl(arg_audit_prog, arg_audit_prog, NULL);

		perror("execl");
		exit(1);
	}
	else if (arg_shell_none) {
		if (arg_debug) {
			int i;
			for (i = cfg.original_program_index; i < cfg.original_argc; i++) {
				if (cfg.original_argv[i] == NULL)
					break;
				printf("execvp argument %d: %s\n", i - cfg.original_program_index, cfg.original_argv[i]);
			}
		}

		if (cfg.original_program_index == 0) {
			fprintf(stderr, "Error: --shell=none configured, but no program specified\n");
			exit(1);
		}

		if (!arg_command && !arg_quiet)
			print_time();

		int rv = ok_to_run(cfg.original_argv[cfg.original_program_index]);

		if (fp) {
			fprintf(fp, "ready\n");
			fclose(fp);
		}
#ifdef HAVE_GCOV
		__gcov_dump();
#endif
#ifdef HAVE_SECCOMP
		seccomp_install_filters();
#endif
		if (rv)
			execvp(cfg.original_argv[cfg.original_program_index], &cfg.original_argv[cfg.original_program_index]);
		else
			fprintf(stderr, "Error: no suitable %s executable found\n", cfg.original_argv[cfg.original_program_index]);
		exit(1);
	}
	else {
		assert(cfg.shell);
		assert(cfg.command_line);

		char *arg[5];
		int index = 0;
		arg[index++] = cfg.shell;
		if (login_shell) {
			arg[index++] = "-l";
			if (arg_debug)
				printf("Starting %s login shell\n", cfg.shell);
		} else {
			arg[index++] = "-c";
			if (arg_debug)
				printf("Running %s command through %s\n", cfg.command_line, cfg.shell);
			if (arg_doubledash)
				arg[index++] = "--";
			arg[index++] = cfg.command_line;
		}
		arg[index] = NULL;
		assert(index < 5);

		if (arg_debug) {
			char *msg;
			if (asprintf(&msg, "sandbox %d, execvp into %s", sandbox_pid, cfg.command_line) == -1)
				errExit("asprintf");
			logmsg(msg);
			free(msg);
		}

		if (arg_debug) {
			int i;
			for (i = 0; i < 5; i++) {
				if (arg[i] == NULL)
					break;
				printf("execvp argument %d: %s\n", i, arg[i]);
			}
		}

		if (!arg_command && !arg_quiet)
			print_time();

		if (fp) {
			fprintf(fp, "ready\n");
			fclose(fp);
		}
#ifdef HAVE_GCOV
		__gcov_dump();
#endif
#ifdef HAVE_SECCOMP
		seccomp_install_filters();
#endif
		execvp(arg[0], arg);
	}

	perror("execvp");
	exit(1); // it should never get here!!!
}
