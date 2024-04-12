create_task_done (GObject      *source_object,
                  GAsyncResult *res,
                  gpointer      user_data)
{
    CreateJob *job;

    job = user_data;
    if (job->done_callback)
    {
        job->done_callback (job->created_file,
                            !job_aborted ((CommonJob *) job),
                            job->done_callback_data);
    }

    g_object_unref (job->dest_dir);
    if (job->src)
    {
        g_object_unref (job->src);
    }
    g_free (job->src_data);
    g_free (job->filename);
    if (job->created_file)
    {
        g_object_unref (job->created_file);
    }

    finalize_common ((CommonJob *) job);

    nautilus_file_changes_consume_changes (TRUE);
}
