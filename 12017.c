static ssize_t handle_llistxattr(FsContext *ctx, V9fsPath *fs_path,
                                 void *value, size_t size)
{
    int fd, ret;
    struct handle_data *data = (struct handle_data *)ctx->private;

    fd = open_by_handle(data->mountfd, fs_path->data, O_NONBLOCK);
    if (fd < 0) {
        return fd;
    }
    ret = flistxattr(fd, value, size);
    close(fd);
    return ret;
}
