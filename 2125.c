static int font_load_and_wait(const char *vc, const char *font, const char *map, const char *unimap) {
        const char *args[9];
        unsigned i = 0;
        pid_t pid;
        int r;

        /* Any part can be set independently */
        if (isempty(font) && isempty(map) && isempty(unimap))
                return 0;

        args[i++] = KBD_SETFONT;
        args[i++] = "-C";
        args[i++] = vc;
        if (!isempty(map)) {
                args[i++] = "-m";
                args[i++] = map;
        }
        if (!isempty(unimap)) {
                args[i++] = "-u";
                args[i++] = unimap;
        }
        if (!isempty(font))
                args[i++] = font;
        args[i++] = NULL;

        if (DEBUG_LOGGING) {
                _cleanup_free_ char *cmd;

                cmd = strv_join((char**) args, " ");
                log_debug("Executing \"%s\"...", strnull(cmd));
        }

        r = safe_fork("(setfont)", FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS|FORK_RLIMIT_NOFILE_SAFE|FORK_LOG, &pid);
        if (r < 0)
                return r;
        if (r == 0) {
                execv(args[0], (char **) args);
                _exit(EXIT_FAILURE);
        }

        return wait_for_terminate_and_check(KBD_SETFONT, pid, WAIT_LOG);
}
