base::string16 SaveCardBubbleControllerImpl::GetWindowTitle() const {
  return l10n_util::GetStringUTF16(
      is_uploading_ ? IDS_AUTOFILL_SAVE_CARD_PROMPT_TITLE_TO_CLOUD
                    : IDS_AUTOFILL_SAVE_CARD_PROMPT_TITLE_LOCAL);
}
