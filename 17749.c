void FileReaderLoader::Start(scoped_refptr<BlobDataHandle> blob_data) {
#if DCHECK_IS_ON()
  DCHECK(!started_loading_) << "FileReaderLoader can only be used once";
  started_loading_ = true;
#endif  // DCHECK_IS_ON()

  MojoCreateDataPipeOptions options;
  options.struct_size = sizeof(MojoCreateDataPipeOptions);
  options.flags = MOJO_CREATE_DATA_PIPE_FLAG_NONE;
  options.element_num_bytes = 1;
  options.capacity_num_bytes =
      blink::BlobUtils::GetDataPipeCapacity(blob_data->size());

  mojo::ScopedDataPipeProducerHandle producer_handle;
  MojoResult rv = CreateDataPipe(&options, &producer_handle, &consumer_handle_);
  if (rv != MOJO_RESULT_OK) {
    Failed(FileErrorCode::kNotReadableErr, FailureType::kMojoPipeCreation);
    return;
  }

  mojom::blink::BlobReaderClientPtr client_ptr;
  binding_.Bind(MakeRequest(&client_ptr, task_runner_), task_runner_);
  blob_data->ReadAll(std::move(producer_handle), std::move(client_ptr));

  if (IsSyncLoad()) {
    binding_.WaitForIncomingMethodCall();
    if (received_on_complete_)
      return;
    if (!received_all_data_) {
      Failed(FileErrorCode::kNotReadableErr,
             FailureType::kSyncDataNotAllLoaded);
      return;
    }

    binding_.WaitForIncomingMethodCall();
    if (!received_on_complete_) {
      Failed(FileErrorCode::kNotReadableErr,
             FailureType::kSyncOnCompleteNotReceived);
    }
  }
}
