int mkdir_p(const char *path, mode_t mode) {
        int r;

        /* Like mkdir -p */

        if ((r = mkdir_parents(path, mode)) < 0)
                return r;

        if (label_mkdir(path, mode) < 0 && errno != EEXIST)
                return -errno;

        return 0;
}
