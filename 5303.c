void BrowserWindowGtk::ShowOneClickSigninBubble(
      const StartSyncCallback& start_sync_callback) {
  new OneClickSigninBubbleGtk(this, start_sync_callback);
}
