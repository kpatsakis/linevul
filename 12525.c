  Extension* LoadExtension(const std::string& name,
                           std::string* error) {
    return LoadExtensionWithLocation(name, Extension::INTERNAL, error);
  }
