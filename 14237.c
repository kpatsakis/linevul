bool ImageProcessorClient::CreateImageProcessor(
    const ImageProcessor::PortConfig& input_config,
    const ImageProcessor::PortConfig& output_config,
    size_t num_buffers) {
  DCHECK_CALLED_ON_VALID_THREAD(test_main_thread_checker_);
  base::WaitableEvent done(base::WaitableEvent::ResetPolicy::AUTOMATIC,
                           base::WaitableEvent::InitialState::NOT_SIGNALED);
  image_processor_client_thread_.task_runner()->PostTask(
      FROM_HERE, base::BindOnce(&ImageProcessorClient::CreateImageProcessorTask,
                                base::Unretained(this), std::cref(input_config),
                                std::cref(output_config), num_buffers, &done));
  done.Wait();
  if (!image_processor_) {
    LOG(ERROR) << "Failed to create ImageProcessor";
    return false;
  }
  return true;
}
