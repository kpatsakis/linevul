void HWNDMessageHandler::UpdateDwmNcRenderingPolicy() {
  if (base::win::GetVersion() < base::win::VERSION_VISTA)
    return;
  DWMNCRENDERINGPOLICY policy = DWMNCRP_ENABLED;
  if (remove_standard_frame_ || delegate_->IsUsingCustomFrame())
    policy = DWMNCRP_DISABLED;
  DwmSetWindowAttribute(hwnd(), DWMWA_NCRENDERING_POLICY,
                        &policy, sizeof(DWMNCRENDERINGPOLICY));
}
