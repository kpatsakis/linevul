void KioskNextHomeInterfaceBrokerImpl::GetIdentityAccessor(
    ::identity::mojom::IdentityAccessorRequest request) {
  connector_->BindInterface(::identity::mojom::kServiceName,
                            std::move(request));
}
