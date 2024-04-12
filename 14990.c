void OmniboxViewViews::Init() {
  set_controller(this);
  SetTextInputType(ui::TEXT_INPUT_TYPE_URL);
  GetRenderText()->SetElideBehavior(gfx::ELIDE_TAIL);
  GetRenderText()->set_symmetric_selection_visual_bounds(true);

  if (popup_window_mode_)
    SetReadOnly(true);

  if (location_bar_view_) {
    InstallPlaceholderText();
    scoped_template_url_service_observer_.Add(
        model()->client()->GetTemplateURLService());

    popup_view_.reset(
        new OmniboxPopupContentsView(this, model(), location_bar_view_));
  }

  constexpr gfx::Insets kTextfieldInsets(3);
  SetBorder(views::CreateEmptyBorder(kTextfieldInsets));

#if defined(OS_CHROMEOS)
  chromeos::input_method::InputMethodManager::Get()->
      AddCandidateWindowObserver(this);
#endif
}
