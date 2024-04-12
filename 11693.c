void PageInfoBubbleView::OnPermissionChanged(
    const PageInfoUI::PermissionInfo& permission) {
  presenter_->OnSitePermissionChanged(permission.type, permission.setting);
  Layout();
  SizeToContents();
}
