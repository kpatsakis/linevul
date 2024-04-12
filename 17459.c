int get_kernel_consoles(char ***ret) {
        _cleanup_strv_free_ char **l = NULL;
        _cleanup_free_ char *line = NULL;
        const char *p;
        int r;

        assert(ret);

        /* If /sys is mounted read-only this means we are running in some kind of container environment. In that
         * case /sys would reflect the host system, not us, hence ignore the data we can read from it. */
        if (path_is_read_only_fs("/sys") > 0)
                goto fallback;

        r = read_one_line_file("/sys/class/tty/console/active", &line);
        if (r < 0)
                return r;

        p = line;
        for (;;) {
                _cleanup_free_ char *tty = NULL;
                char *path;

                r = extract_first_word(&p, &tty, NULL, 0);
                if (r < 0)
                        return r;
                if (r == 0)
                        break;

                if (streq(tty, "tty0")) {
                        tty = mfree(tty);
                        r = read_one_line_file("/sys/class/tty/tty0/active", &tty);
                        if (r < 0)
                                return r;
                }

                path = strappend("/dev/", tty);
                if (!path)
                        return -ENOMEM;

                if (access(path, F_OK) < 0) {
                        log_debug_errno(errno, "Console device %s is not accessible, skipping: %m", path);
                        free(path);
                        continue;
                }

                r = strv_consume(&l, path);
                if (r < 0)
                        return r;
        }

        if (strv_isempty(l)) {
                log_debug("No devices found for system console");
                goto fallback;
        }

        *ret = TAKE_PTR(l);

        return 0;

fallback:
        r = strv_extend(&l, "/dev/console");
        if (r < 0)
                return r;

        *ret = TAKE_PTR(l);

        return 0;
}
