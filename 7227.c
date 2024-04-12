ExtensionInfo::ExtensionInfo(const DictionaryValue* manifest,
                             const std::string& id,
                             const FilePath& path,
                             Manifest::Location location)
    : extension_id(id),
      extension_path(path),
      extension_location(location) {
  if (manifest)
    extension_manifest.reset(manifest->DeepCopy());
}
