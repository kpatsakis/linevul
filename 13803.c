void ChooserContextBase::NotifyPermissionRevoked(const GURL& requesting_origin,
                                                 const GURL& embedding_origin) {
  for (auto& observer : permission_observer_list_) {
    observer.OnChooserObjectPermissionChanged(guard_content_settings_type_,
                                              data_content_settings_type_);
    observer.OnPermissionRevoked(requesting_origin, embedding_origin);
  }
}
