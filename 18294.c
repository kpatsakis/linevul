nautilus_file_operations_compress (GList                  *files,
                                   GFile                  *output,
                                   AutoarFormat            format,
                                   AutoarFilter            filter,
                                   GtkWindow              *parent_window,
                                   NautilusCreateCallback  done_callback,
                                   gpointer                done_callback_data)
{
    g_autoptr (GTask) task = NULL;
    CompressJob *compress_job;

    compress_job = op_job_new (CompressJob, parent_window);
    compress_job->source_files = g_list_copy_deep (files,
                                                   (GCopyFunc) g_object_ref,
                                                   NULL);
    compress_job->output_file = g_object_ref (output);
    compress_job->format = format;
    compress_job->filter = filter;
    compress_job->done_callback = done_callback;
    compress_job->done_callback_data = done_callback_data;

    inhibit_power_manager ((CommonJob *) compress_job, _("Compressing Files"));

    if (!nautilus_file_undo_manager_is_operating ())
    {
        compress_job->common.undo_info = nautilus_file_undo_info_compress_new (files,
                                                                               output,
                                                                               format,
                                                                               filter);
    }

    task = g_task_new (NULL, compress_job->common.cancellable,
                       compress_task_done, compress_job);
    g_task_set_task_data (task, compress_job, NULL);
    g_task_run_in_thread (task, compress_task_thread_func);
}
