file_info_cancel (NautilusDirectory *directory)
{
    if (directory->details->get_info_in_progress != NULL)
    {
        g_cancellable_cancel (directory->details->get_info_in_progress->cancellable);
        directory->details->get_info_in_progress->directory = NULL;
        directory->details->get_info_in_progress = NULL;
        directory->details->get_info_file = NULL;

        async_job_end (directory, "file info");
    }
}
