void PixelBufferRasterWorkerPool::CheckForCompletedUploads() {
  RasterTaskDeque tasks_with_completed_uploads;

  while (!tasks_with_pending_upload_.empty()) {
    internal::RasterWorkerPoolTask* task =
        tasks_with_pending_upload_.front().get();

    if (!resource_provider()->DidSetPixelsComplete(task->resource()->id()))
      break;

    tasks_with_completed_uploads.push_back(task);
    tasks_with_pending_upload_.pop_front();
  }

  DCHECK(client());
  bool should_force_some_uploads_to_complete =
      shutdown_ || client()->ShouldForceTasksRequiredForActivationToComplete();

  if (should_force_some_uploads_to_complete) {
    RasterTaskDeque tasks_with_uploads_to_force;
    RasterTaskDeque::iterator it = tasks_with_pending_upload_.begin();
    while (it != tasks_with_pending_upload_.end()) {
      internal::RasterWorkerPoolTask* task = it->get();
      DCHECK(pixel_buffer_tasks_.find(task) != pixel_buffer_tasks_.end());

      if (shutdown_ || IsRasterTaskRequiredForActivation(task)) {
        tasks_with_uploads_to_force.push_back(task);
        tasks_with_completed_uploads.push_back(task);
        it = tasks_with_pending_upload_.erase(it);
        continue;
      }

      ++it;
    }

    for (RasterTaskDeque::reverse_iterator it =
         tasks_with_uploads_to_force.rbegin();
         it != tasks_with_uploads_to_force.rend(); ++it) {
      resource_provider()->ForceSetPixelsToComplete((*it)->resource()->id());
      has_performed_uploads_since_last_flush_ = true;
    }
  }

  while (!tasks_with_completed_uploads.empty()) {
    internal::RasterWorkerPoolTask* task =
        tasks_with_completed_uploads.front().get();

    resource_provider()->ReleasePixelBuffer(task->resource()->id());

    bytes_pending_upload_ -= task->resource()->bytes();

    task->DidRun(false);

    DCHECK(std::find(completed_tasks_.begin(),
                     completed_tasks_.end(),
                     task) == completed_tasks_.end());
    completed_tasks_.push_back(task);

    tasks_required_for_activation_.erase(task);

    tasks_with_completed_uploads.pop_front();
  }
}
