void ExtensionInstallPrompt::ShowConfirmation() {
  scoped_ptr<const PermissionSet> permissions_wrapper;
  const PermissionSet* permissions_to_display = nullptr;
  if (custom_permissions_.get()) {
    permissions_to_display = custom_permissions_.get();
  } else if (extension_) {
    extensions::PermissionsUpdater(
        profile_, extensions::PermissionsUpdater::INIT_FLAG_TRANSIENT)
        .InitializePermissions(extension_);
    permissions_to_display =
        &extension_->permissions_data()->active_permissions();
    if (prompt_->type() == DELEGATED_PERMISSIONS_PROMPT ||
        prompt_->type() == DELEGATED_BUNDLE_PERMISSIONS_PROMPT) {
      const PermissionSet& optional_permissions =
          extensions::PermissionsParser::GetOptionalPermissions(extension_);
      permissions_wrapper = PermissionSet::CreateUnion(*permissions_to_display,
                                                       optional_permissions);
      permissions_to_display = permissions_wrapper.get();
    }
  }

  if (permissions_to_display &&
      (!extension_ ||
       !extensions::PermissionsData::ShouldSkipPermissionWarnings(
           extension_->id()))) {
    Manifest::Type type =
        extension_ ? extension_->GetType() : Manifest::TYPE_UNKNOWN;
    const extensions::PermissionMessageProvider* message_provider =
        extensions::PermissionMessageProvider::Get();

    prompt_->SetPermissions(message_provider->GetPermissionMessages(
                                message_provider->GetAllPermissionIDs(
                                    *permissions_to_display, type)),
                            REGULAR_PERMISSIONS);

    const PermissionSet* withheld =
        extension_ ? &extension_->permissions_data()->withheld_permissions()
                   : nullptr;
    if (withheld && !withheld->IsEmpty()) {
      prompt_->SetPermissions(
          message_provider->GetPermissionMessages(
              message_provider->GetAllPermissionIDs(*withheld, type)),
          WITHHELD_PERMISSIONS);
    }
  }

  switch (prompt_->type()) {
    case PERMISSIONS_PROMPT:
    case RE_ENABLE_PROMPT:
    case INLINE_INSTALL_PROMPT:
    case EXTERNAL_INSTALL_PROMPT:
    case INSTALL_PROMPT:
    case POST_INSTALL_PERMISSIONS_PROMPT:
    case REMOTE_INSTALL_PROMPT:
    case REPAIR_PROMPT:
    case DELEGATED_PERMISSIONS_PROMPT: {
      prompt_->set_extension(extension_);
      break;
    }
    case BUNDLE_INSTALL_PROMPT:
    case DELEGATED_BUNDLE_PERMISSIONS_PROMPT: {
      prompt_->set_bundle(bundle_);
      break;
    }
    case LAUNCH_PROMPT_DEPRECATED:
    default:
      NOTREACHED() << "Unknown message";
      return;
  }
  prompt_->set_delegated_username(delegated_username_);
  prompt_->set_icon(gfx::Image::CreateFrom1xBitmap(icon_));

  g_last_prompt_type_for_tests = prompt_->type();

  if (AutoConfirmPrompt(delegate_))
    return;

  if (show_params_->WasParentDestroyed()) {
    delegate_->InstallUIAbort(false);
    return;
  }

  if (show_dialog_callback_.is_null())
    GetDefaultShowDialogCallback().Run(show_params_.get(), delegate_, prompt_);
  else
    show_dialog_callback_.Run(show_params_.get(), delegate_, prompt_);
}
