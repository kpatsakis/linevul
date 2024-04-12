void Dispatcher::OnUpdateTabSpecificPermissions(const GURL& visible_url,
                                                const std::string& extension_id,
                                                const URLPatternSet& new_hosts,
                                                bool update_origin_whitelist,
                                                int tab_id) {
  const Extension* extension =
      RendererExtensionRegistry::Get()->GetByID(extension_id);
  if (!extension)
    return;

  URLPatternSet old_effective =
      extension->permissions_data()->GetEffectiveHostPermissions();
  extension->permissions_data()->UpdateTabSpecificPermissions(
      tab_id,
      extensions::PermissionSet(extensions::APIPermissionSet(),
                                extensions::ManifestPermissionSet(), new_hosts,
                                extensions::URLPatternSet()));

  if (update_origin_whitelist) {
    UpdateOriginPermissions(
        extension->url(),
        old_effective,
        extension->permissions_data()->GetEffectiveHostPermissions());
  }
}
