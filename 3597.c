void BackendIO::ExecuteEntryOperation() {
  switch (operation_) {
    case OP_READ:
      result_ =
          entry_->ReadDataImpl(index_, offset_, buf_.get(), buf_len_,
                               base::Bind(&BackendIO::OnIOComplete, this));
      break;
    case OP_WRITE:
      result_ =
          entry_->WriteDataImpl(index_, offset_, buf_.get(), buf_len_,
                                base::Bind(&BackendIO::OnIOComplete, this),
                                truncate_);
      break;
    case OP_READ_SPARSE:
      result_ = entry_->ReadSparseDataImpl(
                    offset64_, buf_.get(), buf_len_,
                    base::Bind(&BackendIO::OnIOComplete, this));
      break;
    case OP_WRITE_SPARSE:
      result_ = entry_->WriteSparseDataImpl(
                    offset64_, buf_.get(), buf_len_,
                    base::Bind(&BackendIO::OnIOComplete, this));
      break;
    case OP_GET_RANGE:
      result_ = entry_->GetAvailableRangeImpl(offset64_, buf_len_, start_);
      break;
    case OP_CANCEL_IO:
      entry_->CancelSparseIOImpl();
      result_ = net::OK;
      break;
    case OP_IS_READY:
      result_ = entry_->ReadyForSparseIOImpl(
                    base::Bind(&BackendIO::OnIOComplete, this));
      break;
    default:
      NOTREACHED() << "Invalid Operation";
      result_ = net::ERR_UNEXPECTED;
  }
  buf_ = NULL;
  if (result_ != net::ERR_IO_PENDING)
    NotifyController();
}
