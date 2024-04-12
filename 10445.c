  void ScheduleNextTask() {
    DCHECK(io_runner->BelongsToCurrentThread());
    if (task_stack_.empty()) {
      return;
    }
    base::SequencedTaskRunnerHandle::Get()->PostTask(
        FROM_HERE, std::move(task_stack_.top()));
    task_stack_.pop();
  }
