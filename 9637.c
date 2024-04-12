static int handle_mknod(FsContext *fs_ctx, V9fsPath *dir_path,
                       const char *name, FsCred *credp)
{
    int dirfd, ret;
    struct handle_data *data = (struct handle_data *)fs_ctx->private;

    dirfd = open_by_handle(data->mountfd, dir_path->data, O_PATH);
    if (dirfd < 0) {
        return dirfd;
    }
    ret = mknodat(dirfd, name, credp->fc_mode, credp->fc_rdev);
    if (!ret) {
        ret = handle_update_file_cred(dirfd, name, credp);
    }
    close(dirfd);
    return ret;
}
