void KeyboardOverlayUIHTMLSource::StartDataRequest(const std::string& path,
                                                   bool is_incognito,
                                                   int request_id) {
  DictionaryValue localized_strings;
  for (size_t i = 0; i < arraysize(kI18nContentToMessage); ++i) {
    localized_strings.SetString(
        kI18nContentToMessage[i].i18n_content,
        l10n_util::GetStringUTF16(kI18nContentToMessage[i].message));
  }

  static const base::StringPiece keyboard_overlay_html(
      ResourceBundle::GetSharedInstance().GetRawDataResource(
          IDR_KEYBOARD_OVERLAY_HTML));
  std::string full_html = jstemplate_builder::GetI18nTemplateHtml(
      keyboard_overlay_html, &localized_strings);

  SendResponse(request_id, base::RefCountedString::TakeString(&full_html));
}
