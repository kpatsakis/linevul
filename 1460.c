bool ExtensionRegistry::AddBlacklisted(
    const scoped_refptr<const Extension>& extension) {
  return blacklisted_extensions_.Insert(extension);
}
