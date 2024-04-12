base::string16 OmniboxViewViews::GetGrayTextAutocompletion() const {
#if defined(OS_WIN) || defined(USE_AURA)
  return location_bar_view_->GetGrayTextAutocompletion();
#else
  return base::string16();
#endif
}
