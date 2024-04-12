unsigned PixelBufferRasterWorkerPool::PendingRasterTaskCount() const {
  unsigned num_completed_raster_tasks =
      tasks_with_pending_upload_.size() + completed_tasks_.size();
  DCHECK_GE(pixel_buffer_tasks_.size(), num_completed_raster_tasks);
  return pixel_buffer_tasks_.size() - num_completed_raster_tasks;
}
