VirtualAuthenticator::VirtualAuthenticator(
    ::device::FidoTransportProtocol transport)
    : transport_(transport),
      unique_id_(base::GenerateGUID()),
      state_(base::MakeRefCounted<::device::VirtualFidoDevice::State>()) {}
