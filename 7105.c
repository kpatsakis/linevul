bool ContainsWebstoreTile(content::RenderFrameHost* iframe) {
  int num_webstore_tiles = 0;
  EXPECT_TRUE(instant_test_utils::GetIntFromJS(
      iframe,
      "document.querySelectorAll(\".md-tile[href='" +
          l10n_util::GetStringUTF8(IDS_WEBSTORE_URL) + "']\").length",
      &num_webstore_tiles));
  return num_webstore_tiles == 1;
}
