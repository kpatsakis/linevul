UsbChooserContext::GetGrantedObjects(const GURL& requesting_origin,
                                     const GURL& embedding_origin) {
  std::vector<std::unique_ptr<base::DictionaryValue>> objects =
      ChooserContextBase::GetGrantedObjects(requesting_origin,
                                            embedding_origin);

  if (CanRequestObjectPermission(requesting_origin, embedding_origin)) {
    auto it = ephemeral_devices_.find(
        std::make_pair(requesting_origin, embedding_origin));
    if (it != ephemeral_devices_.end()) {
      for (const std::string& guid : it->second) {
        auto dict_it = ephemeral_dicts_.find(guid);
        DCHECK(dict_it != ephemeral_dicts_.end());
        objects.push_back(dict_it->second.CreateDeepCopy());
      }
    }
  }

  return objects;
}
