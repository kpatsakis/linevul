  void InitializeClientProcess(mojom::ProcessType process_type) {
    mdm_ = MemoryDumpManager::CreateInstanceForTesting();
    mdm_->set_dumper_registrations_ignored_for_testing(true);
    const char* kServiceName = "TestServiceName";
    ClientProcessImpl::Config config(nullptr, kServiceName, process_type);
    config.coordinator_for_testing = coordinator_.get();
    client_process_.reset(new ClientProcessImpl(config));
  }
