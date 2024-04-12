SendTabToSelfInfoBar::SendTabToSelfInfoBar(
    std::unique_ptr<SendTabToSelfInfoBarDelegate> delegate)
    : InfoBarAndroid(std::move(delegate)) {}
