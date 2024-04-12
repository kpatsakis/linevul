DaemonProcess::DaemonProcess(
    scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner,
    scoped_refptr<base::SingleThreadTaskRunner> io_task_runner,
    const base::Closure& stopped_callback)
    : Stoppable(caller_task_runner, stopped_callback),
      caller_task_runner_(caller_task_runner),
      io_task_runner_(io_task_runner),
      next_terminal_id_(0) {
  DCHECK(caller_task_runner->BelongsToCurrentThread());
}
