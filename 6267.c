WebExternalPopupMenu* RenderViewImpl::createExternalPopupMenu(
    const WebPopupMenuInfo& popup_menu_info,
    WebExternalPopupMenuClient* popup_menu_client) {
  DCHECK(!external_popup_menu_.get());
  external_popup_menu_.reset(
      new ExternalPopupMenu(this, popup_menu_info, popup_menu_client));
  return external_popup_menu_.get();
}
