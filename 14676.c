void vnc_job_push(VncJob *job)
{
    vnc_lock_queue(queue);
    if (queue->exit || QLIST_EMPTY(&job->rectangles)) {
        g_free(job);
    } else {
        QTAILQ_INSERT_TAIL(&queue->jobs, job, next);
        qemu_cond_broadcast(&queue->cond);
    }
    vnc_unlock_queue(queue);
}
