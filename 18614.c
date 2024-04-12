bool MatchesFilter(const std::string* device_name,
                   const UUIDSet& device_uuids,
                   const blink::mojom::WebBluetoothLeScanFilterPtr& filter) {
  if (filter->name) {
    if (device_name == nullptr)
      return false;
    if (filter->name.value() != *device_name)
      return false;
  }

  if (filter->name_prefix && filter->name_prefix->size()) {
    if (device_name == nullptr)
      return false;
    if (!base::StartsWith(*device_name, filter->name_prefix.value(),
                          base::CompareCase::SENSITIVE))
      return false;
  }

  if (filter->services) {
    for (const auto& service : filter->services.value()) {
      if (!base::Contains(device_uuids, service)) {
        return false;
      }
    }
  }

  return true;
}
