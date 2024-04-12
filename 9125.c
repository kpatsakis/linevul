void BrowserView::ExecuteExtensionCommand(
    const extensions::Extension* extension,
    const extensions::Command& command) {
  extension_keybinding_registry_->ExecuteCommand(extension->id(),
                                                 command.accelerator());
}
