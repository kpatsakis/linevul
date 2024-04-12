void AbortRequestBeforeItStarts(
    IPC::Sender* sender,
    int request_id,
    network::mojom::URLLoaderClientPtr url_loader_client) {
  network::URLLoaderCompletionStatus status;
  status.error_code = net::ERR_ABORTED;
  status.exists_in_cache = false;
  status.completion_time = base::TimeTicks();
  status.encoded_data_length = 0;
  status.encoded_body_length = 0;
  url_loader_client->OnComplete(status);
}
