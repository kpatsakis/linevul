std::unique_ptr<service_manager::Service> CreateDataDecoderService() {
  content::UtilityThread::Get()->EnsureBlinkInitialized();
  return data_decoder::DataDecoderService::Create();
}
