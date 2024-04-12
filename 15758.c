scoped_refptr<const Extension> GetExtensionWithHostPermission(
    const std::string& id,
    const std::string& host_permissions,
    Manifest::Location location) {
  ListBuilder permissions;
  if (!host_permissions.empty())
    permissions.Append(host_permissions);

  return ExtensionBuilder()
      .SetManifest(
          DictionaryBuilder()
              .Set("name", id)
              .Set("description", "an extension")
              .Set("manifest_version", 2)
              .Set("version", "1.0.0")
              .Set("permissions", permissions.Pass())
              .Build())
      .SetLocation(location)
      .SetID(id)
      .Build();
}
