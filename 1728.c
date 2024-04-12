int open_terminal_in_namespace(pid_t pid, const char *name, int mode) {
        _cleanup_close_ int pidnsfd = -1, mntnsfd = -1, usernsfd = -1, rootfd = -1;
        _cleanup_close_pair_ int pair[2] = { -1, -1 };
        pid_t child;
        int r;

        r = namespace_open(pid, &pidnsfd, &mntnsfd, NULL, &usernsfd, &rootfd);
        if (r < 0)
                return r;

        if (socketpair(AF_UNIX, SOCK_DGRAM, 0, pair) < 0)
                return -errno;

        r = namespace_fork("(sd-terminalns)", "(sd-terminal)", NULL, 0, FORK_RESET_SIGNALS|FORK_DEATHSIG,
                           pidnsfd, mntnsfd, -1, usernsfd, rootfd, &child);
        if (r < 0)
                return r;
        if (r == 0) {
                int master;

                pair[0] = safe_close(pair[0]);

                master = open_terminal(name, mode|O_NOCTTY|O_CLOEXEC);
                if (master < 0)
                        _exit(EXIT_FAILURE);

                if (send_one_fd(pair[1], master, 0) < 0)
                        _exit(EXIT_FAILURE);

                _exit(EXIT_SUCCESS);
        }

        pair[1] = safe_close(pair[1]);

        r = wait_for_terminate_and_check("(sd-terminalns)", child, 0);
        if (r < 0)
                return r;
        if (r != EXIT_SUCCESS)
                return -EIO;

        return receive_one_fd(pair[0], 0);
}
