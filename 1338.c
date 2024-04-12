void PaymentRequestState::AreRequestedMethodsSupported(
    StatusCallback callback) {
  if (!get_all_instruments_finished_) {
    are_requested_methods_supported_callback_ = std::move(callback);
    return;
  }

  base::ThreadTaskRunnerHandle::Get()->PostTask(
      FROM_HERE,
      base::BindOnce(&PaymentRequestState::CheckRequestedMethodsSupported,
                     weak_ptr_factory_.GetWeakPtr(), std::move(callback)));
}
