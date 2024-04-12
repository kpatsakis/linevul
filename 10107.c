static ssize_t handle_readlink(FsContext *fs_ctx, V9fsPath *fs_path,
                               char *buf, size_t bufsz)
{
    int fd, ret;
    struct handle_data *data = (struct handle_data *)fs_ctx->private;

    fd = open_by_handle(data->mountfd, fs_path->data, O_PATH);
    if (fd < 0) {
        return fd;
    }
    ret = readlinkat(fd, "", buf, bufsz);
    close(fd);
    return ret;
}
