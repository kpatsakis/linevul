void BeforeTranslateInfoBar::RunMenu(views::View* source,
                                     const gfx::Point& pt) {
  if (source == language_menu_button_) {
    if (!languages_menu_.get())
      languages_menu_.reset(new views::Menu2(&languages_menu_model_));
    languages_menu_->RunMenuAt(pt, views::Menu2::ALIGN_TOPRIGHT);
  } else if (source == options_menu_button_) {
    if (!options_menu_.get())
      options_menu_.reset(new views::Menu2(&options_menu_model_));
    options_menu_->RunMenuAt(pt, views::Menu2::ALIGN_TOPRIGHT);
  } else {
    NOTREACHED();
  }
}
