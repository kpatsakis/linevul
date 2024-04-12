static void vdagent_file_xfer_task_free(gpointer data)
{
    AgentFileXferTask *task = data;

    g_return_if_fail(task != NULL);

    if (task->file_fd > 0) {
        syslog(LOG_ERR, "file-xfer: Removing task %u and file %s due to error",
               task->id, task->file_name);
        close(task->file_fd);
        unlink(task->file_name);
    } else if (task->debug)
        syslog(LOG_DEBUG, "file-xfer: Removing task %u %s",
               task->id, task->file_name);

    g_free(task->file_name);
    g_free(task);
}
