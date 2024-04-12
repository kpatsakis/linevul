WtsConsoleSessionProcessDriver::WtsConsoleSessionProcessDriver(
    const base::Closure& stopped_callback,
    WtsConsoleMonitor* monitor,
    scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner,
    scoped_refptr<base::SingleThreadTaskRunner> io_task_runner)
    : Stoppable(caller_task_runner, stopped_callback),
      caller_task_runner_(caller_task_runner),
      io_task_runner_(io_task_runner),
      monitor_(monitor) {
  monitor_->AddWtsConsoleObserver(this);
}
