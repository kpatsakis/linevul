  virtual std::wstring GetButtonLabel(InfoBarButton button) const {
    return button == BUTTON_OK ?
        l10n_util::GetString(IDS_SET_AS_DEFAULT_INFOBAR_BUTTON_LABEL) :
        l10n_util::GetString(IDS_DONT_ASK_AGAIN_INFOBAR_BUTTON_LABEL);
  }
