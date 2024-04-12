bool Extension::LoadLaunchContainer(string16* error) {
  Value* tmp_launcher_container = NULL;
  if (!manifest_->Get(keys::kLaunchContainer, &tmp_launcher_container))
    return true;

  std::string launch_container_string;
  if (!tmp_launcher_container->GetAsString(&launch_container_string)) {
    *error = ASCIIToUTF16(errors::kInvalidLaunchContainer);
    return false;
  }

  if (launch_container_string == values::kLaunchContainerPanel) {
    launch_container_ = extension_misc::LAUNCH_PANEL;
  } else if (launch_container_string == values::kLaunchContainerTab) {
    launch_container_ = extension_misc::LAUNCH_TAB;
  } else {
    *error = ASCIIToUTF16(errors::kInvalidLaunchContainer);
    return false;
  }

  bool can_specify_initial_size =
      launch_container_ == extension_misc::LAUNCH_PANEL ||
      launch_container_ == extension_misc::LAUNCH_WINDOW;

  if (!ReadLaunchDimension(manifest_.get(),
                           keys::kLaunchWidth,
                           &launch_width_,
                           can_specify_initial_size,
                           error)) {
      return false;
  }

  if (!ReadLaunchDimension(manifest_.get(),
                           keys::kLaunchHeight,
                           &launch_height_,
                           can_specify_initial_size,
                           error)) {
      return false;
  }

  return true;
}
