void TranslateInfoBarDelegate::InfoBarDismissed() {
  if (step_ != translate::TRANSLATE_STEP_BEFORE_TRANSLATE)
    return;

  TranslationDeclined();
  UMA_HISTOGRAM_BOOLEAN("Translate.DeclineTranslateCloseInfobar", true);
}
