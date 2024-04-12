bool TranslateInfoBarDelegate::ShouldShowNeverTranslateShortcut() {
  DCHECK_EQ(translate::TRANSLATE_STEP_BEFORE_TRANSLATE, step_);
  return !GetWebContents()->GetBrowserContext()->IsOffTheRecord() &&
      (prefs_->GetTranslationDeniedCount(original_language_code()) >=
          kNeverTranslateMinCount);
}
