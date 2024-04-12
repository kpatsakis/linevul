GuestViewBase* ExtensionViewGuest::Create(WebContents* owner_web_contents) {
  return new ExtensionViewGuest(owner_web_contents);
}
