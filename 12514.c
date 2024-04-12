VideoEncodeAcceleratorClient::VideoEncodeAcceleratorClient(
    VideoEncodeAccelerator::Client* client,
    mojom::VideoEncodeAcceleratorClientRequest request)
    : client_(client), binding_(this, std::move(request)) {
  DCHECK(client_);
}
