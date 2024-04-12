void BrowserLauncherItemController::Close() {
  views::Widget* widget = views::Widget::GetWidgetForNativeView(window_);
  if (widget)
    widget->Close();
}
