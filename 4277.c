SkColor DialogNotification::GetBackgroundColor() const {
  switch (type_) {
    case DialogNotification::WALLET_USAGE_CONFIRMATION:
      return SkColorSetRGB(0xf5, 0xf5, 0xf5);
    case DialogNotification::REQUIRED_ACTION:
    case DialogNotification::WALLET_ERROR:
      return SkColorSetRGB(0xfc, 0xf3, 0xbf);
    case DialogNotification::DEVELOPER_WARNING:
    case DialogNotification::SECURITY_WARNING:
      return kWarningColor;
    case DialogNotification::NONE:
      return SK_ColorTRANSPARENT;
  }

  NOTREACHED();
  return SK_ColorTRANSPARENT;
}
