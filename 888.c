request_is_satisfied (NautilusDirectory *directory,
                      NautilusFile      *file,
                      Request            request)
{
    if (REQUEST_WANTS_TYPE (request, REQUEST_FILE_LIST) &&
        !(directory->details->directory_loaded &&
          directory->details->directory_loaded_sent_notification))
    {
        return FALSE;
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_DIRECTORY_COUNT))
    {
        if (has_problem (directory, file, lacks_directory_count))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_FILE_INFO))
    {
        if (has_problem (directory, file, lacks_info))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_FILESYSTEM_INFO))
    {
        if (has_problem (directory, file, lacks_filesystem_info))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_DEEP_COUNT))
    {
        if (has_problem (directory, file, lacks_deep_count))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_THUMBNAIL))
    {
        if (has_problem (directory, file, lacks_thumbnail))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_MOUNT))
    {
        if (has_problem (directory, file, lacks_mount))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_MIME_LIST))
    {
        if (has_problem (directory, file, lacks_mime_list))
        {
            return FALSE;
        }
    }

    if (REQUEST_WANTS_TYPE (request, REQUEST_LINK_INFO))
    {
        if (has_problem (directory, file, lacks_link_info))
        {
            return FALSE;
        }
    }

    return TRUE;
}
