void ExtensionOptionsGuest::OnPreferredSizeChanged(const gfx::Size& pref_size) {
  extension_options_internal::PreferredSizeChangedOptions options;
  options.width = PhysicalPixelsToLogicalPixels(pref_size.width());
  options.height = PhysicalPixelsToLogicalPixels(pref_size.height());
  DispatchEventToView(make_scoped_ptr(new GuestViewEvent(
      extension_options_internal::OnPreferredSizeChanged::kEventName,
      options.ToValue())));
}
