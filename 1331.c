static int handle_link(FsContext *ctx, V9fsPath *oldpath,
                       V9fsPath *dirpath, const char *name)
{
    int oldfd, newdirfd, ret;
    struct handle_data *data = (struct handle_data *)ctx->private;

    oldfd = open_by_handle(data->mountfd, oldpath->data, O_PATH);
    if (oldfd < 0) {
        return oldfd;
    }
    newdirfd = open_by_handle(data->mountfd, dirpath->data, O_PATH);
    if (newdirfd < 0) {
        close(oldfd);
        return newdirfd;
    }
    ret = linkat(oldfd, "", newdirfd, name, AT_EMPTY_PATH);
    close(newdirfd);
    close(oldfd);
    return ret;
}
