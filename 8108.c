void MultibufferDataSource::Read(int64_t position,
                                 int size,
                                 uint8_t* data,
                                 const DataSource::ReadCB& read_cb) {
  DVLOG(1) << "Read: " << position << " offset, " << size << " bytes";
  DCHECK(!init_cb_);
  DCHECK(read_cb);

  {
    base::AutoLock auto_lock(lock_);
    DCHECK(!read_op_);

    if (stop_signal_received_) {
      read_cb.Run(kReadError);
      return;
    }

    if (reader_) {
      int bytes_read = reader_->TryReadAt(position, data, size);
      if (bytes_read > 0) {
        bytes_read_ += bytes_read;
        seek_positions_.push_back(position + bytes_read);
        if (seek_positions_.size() == 1) {
          render_task_runner_->PostDelayedTask(
              FROM_HERE,
              base::Bind(&MultibufferDataSource::SeekTask,
                         weak_factory_.GetWeakPtr()),
              kSeekDelay);
        }

        read_cb.Run(bytes_read);
        return;
      }
    }
    read_op_.reset(new ReadOperation(position, size, data, read_cb));
  }

  render_task_runner_->PostTask(
      FROM_HERE,
      base::Bind(&MultibufferDataSource::ReadTask, weak_factory_.GetWeakPtr()));
}
