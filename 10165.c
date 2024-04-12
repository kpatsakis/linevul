AfterTranslateInfoBar::AfterTranslateInfoBar(
    TranslateInfoBarDelegate* delegate)
    : TranslateInfoBarBase(delegate),
      original_language_menu_model_(delegate, LanguagesMenuModel::ORIGINAL),
      target_language_menu_model_(delegate, LanguagesMenuModel::TARGET),
      options_menu_model_(delegate),
      swapped_language_buttons_(false) {
  std::vector<string16> strings;
  TranslateInfoBarDelegate::GetAfterTranslateStrings(
      &strings, &swapped_language_buttons_);
  DCHECK(strings.size() == 3U);

  label_1_ = CreateLabel(strings[0]);
  AddChildView(label_1_);

  label_2_ = CreateLabel(strings[1]);
  AddChildView(label_2_);

  label_3_ = CreateLabel(strings[2]);
  AddChildView(label_3_);

  original_language_menu_button_ = CreateMenuButton(string16(), true, this);
  AddChildView(original_language_menu_button_);

  target_language_menu_button_ = CreateMenuButton(string16(), true, this);
  AddChildView(target_language_menu_button_);

  options_menu_button_ =
      CreateMenuButton(l10n_util::GetStringUTF16(IDS_TRANSLATE_INFOBAR_OPTIONS),
                       false, this);
  AddChildView(options_menu_button_);

  revert_button_ = InfoBarTextButton::Create(this,
      l10n_util::GetStringUTF16(IDS_TRANSLATE_INFOBAR_REVERT));
  AddChildView(revert_button_);

  UpdateLanguageButtonText(LanguagesMenuModel::ORIGINAL);
  UpdateLanguageButtonText(LanguagesMenuModel::TARGET);
}
