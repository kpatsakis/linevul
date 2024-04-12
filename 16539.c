void ExtensionInstalledBubbleGtk::Show(const Extension* extension,
                                       Browser* browser,
                                       const SkBitmap& icon) {
  new ExtensionInstalledBubbleGtk(extension, browser, icon);
}
