std::unique_ptr<infobars::InfoBar> InfoBarService::CreateConfirmInfoBar(
    std::unique_ptr<ConfirmInfoBarDelegate> delegate) {
#if defined(OS_MACOSX)
  if (views_mode_controller::IsViewsBrowserCocoa())
    return InfoBarService::CreateConfirmInfoBarCocoa(std::move(delegate));
#endif
  return std::make_unique<ConfirmInfoBar>(std::move(delegate));
}
