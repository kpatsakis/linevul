get_target_file (GFile      *src,
                 GFile      *dest_dir,
                 const char *dest_fs_type,
                 gboolean    same_fs)
{
    return get_target_file_with_custom_name (src, dest_dir, dest_fs_type, same_fs, NULL);
}
