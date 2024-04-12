const Extension* ExtensionBrowserTest::LoadExtensionIncognito(
    const base::FilePath& path) {
  return LoadExtensionWithFlags(path,
                                kFlagEnableFileAccess | kFlagEnableIncognito);
}
