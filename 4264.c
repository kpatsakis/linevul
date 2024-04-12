lacks_mount (NautilusFile *file)
{
    return (!file->details->mount_is_up_to_date &&
            (
                /* Unix mountpoint, could be a GMount */
                file->details->is_mountpoint ||

                /* The toplevel directory of something */
                (file->details->type == G_FILE_TYPE_DIRECTORY &&
                 nautilus_file_is_self_owned (file)) ||

                /* Mountable, could be a mountpoint */
                (file->details->type == G_FILE_TYPE_MOUNTABLE)

            )
            );
}
