  scoped_refptr<Extension> LoadExtension(DictionaryValue* value,
                                         std::string* error) {
    return LoadExtensionWithLocation(value, Extension::INTERNAL, false, error);
  }
