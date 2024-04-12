  void StartOnIOThread() {
    DCHECK(io_thread_checker_.CalledOnValidThread());
    service_context_.reset(new service_manager::ServiceContext(
        base::MakeUnique<service_manager::ForwardingService>(this),
        std::move(pending_service_request_),
        std::move(io_thread_connector_),
        std::move(pending_connector_request_)));

    message_loop_observer_ =
        new MessageLoopObserver(weak_factory_.GetWeakPtr());
  }
