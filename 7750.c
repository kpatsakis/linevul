void PaymentRequestState::HasEnrolledInstrument(StatusCallback callback) {
  if (!get_all_instruments_finished_) {
    DCHECK(!has_enrolled_instrument_callback_);
    has_enrolled_instrument_callback_ = std::move(callback);
    return;
  }

  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE,
      base::BindOnce(&PaymentRequestState::CheckHasEnrolledInstrument,
                     weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
}
