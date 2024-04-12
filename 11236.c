int reset_terminal(const char *name) {
        _cleanup_close_ int fd = -1;

        /* We open the terminal with O_NONBLOCK here, to ensure we
         * don't block on carrier if this is a terminal with carrier
         * configured. */

        fd = open_terminal(name, O_RDWR|O_NOCTTY|O_CLOEXEC|O_NONBLOCK);
        if (fd < 0)
                return fd;

        return reset_terminal_fd(fd, true);
}
