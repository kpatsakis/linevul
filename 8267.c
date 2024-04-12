void DataReductionProxyIOData::Clone(mojom::DataReductionProxyRequest request) {
  drp_bindings_.AddBinding(this, std::move(request));
}
