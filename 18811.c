bool V4L2JpegEncodeAccelerator::EncodedInstanceDmaBuf::EnqueueInputRecord() {
  DCHECK(parent_->encoder_task_runner_->BelongsToCurrentThread());
  DCHECK(!input_job_queue_.empty());
  DCHECK(!free_input_buffers_.empty());

  std::unique_ptr<JobRecord> job_record = std::move(input_job_queue_.front());
  input_job_queue_.pop();
  const int index = free_input_buffers_.back();

  struct v4l2_buffer qbuf;
  struct v4l2_plane planes[kMaxNV12Plane];
  memset(&qbuf, 0, sizeof(qbuf));
  memset(planes, 0, sizeof(planes));
  qbuf.index = index;
  qbuf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE;
  qbuf.memory = V4L2_MEMORY_DMABUF;
  qbuf.length = base::size(planes);
  qbuf.m.planes = planes;

  const auto& frame = job_record->input_frame;
  for (size_t i = 0; i < input_buffer_num_planes_; i++) {
    if (device_input_layout_->is_multi_planar()) {
      qbuf.m.planes[i].bytesused = base::checked_cast<__u32>(
          VideoFrame::PlaneSize(frame->format(), i,
                                device_input_layout_->coded_size())
              .GetArea());
    } else {
      qbuf.m.planes[i].bytesused = VideoFrame::AllocationSize(
          frame->format(), device_input_layout_->coded_size());
    }

    const auto& fds = frame->DmabufFds();
    const auto& planes = frame->layout().planes();
    qbuf.m.planes[i].m.fd = (i < fds.size()) ? fds[i].get() : fds.back().get();
    qbuf.m.planes[i].data_offset = planes[i].offset;
    qbuf.m.planes[i].bytesused += qbuf.m.planes[i].data_offset;
    qbuf.m.planes[i].length =
        planes[i].size + qbuf.m.planes[i].data_offset;
  }

  IOCTL_OR_ERROR_RETURN_FALSE(VIDIOC_QBUF, &qbuf);
  running_job_queue_.push(std::move(job_record));
  free_input_buffers_.pop_back();
  return true;
}
