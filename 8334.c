void CardUnmaskPromptViews::InitIfNecessary() {
  if (has_children())
    return;

  main_contents_ = new views::View();
  main_contents_->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kVertical, 0, 0, 10));
  AddChildView(main_contents_);

  permanent_error_label_ = new views::Label();
  permanent_error_label_->set_background(
      views::Background::CreateSolidBackground(
          SkColorSetRGB(0xdb, 0x44, 0x37)));
  permanent_error_label_->SetBorder(
      views::Border::CreateEmptyBorder(10, kEdgePadding, 10, kEdgePadding));
  permanent_error_label_->SetEnabledColor(SK_ColorWHITE);
  permanent_error_label_->SetAutoColorReadabilityEnabled(false);
  permanent_error_label_->SetVisible(false);
  permanent_error_label_->SetMultiLine(true);
  permanent_error_label_->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  main_contents_->AddChildView(permanent_error_label_);

  views::View* controls_container = new views::View();
  controls_container->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kVertical, kEdgePadding, 0, 0));
  main_contents_->AddChildView(controls_container);

  views::Label* instructions =
      new views::Label(controller_->GetInstructionsMessage());

  instructions->SetMultiLine(true);
  instructions->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  instructions->SetBorder(views::Border::CreateEmptyBorder(0, 0, 15, 0));
  controls_container->AddChildView(instructions);

  input_row_ = new views::View();
  input_row_->SetLayoutManager(
      new views::BoxLayout(views::BoxLayout::kHorizontal, 0, 0, 5));
  controls_container->AddChildView(input_row_);

  if (controller_->ShouldRequestExpirationDate()) {
    month_input_ = new views::Combobox(&month_combobox_model_);
    month_input_->set_listener(this);
    input_row_->AddChildView(month_input_);
    input_row_->AddChildView(new views::Label(l10n_util::GetStringUTF16(
        IDS_AUTOFILL_CARD_UNMASK_EXPIRATION_DATE_SEPARATOR)));
    year_input_ = new views::Combobox(&year_combobox_model_);
    year_input_->set_listener(this);
    input_row_->AddChildView(year_input_);
    input_row_->AddChildView(new views::Label(base::ASCIIToUTF16("    ")));
  }

  cvc_input_ = new DecoratedTextfield(
      base::string16(),
      l10n_util::GetStringUTF16(IDS_AUTOFILL_DIALOG_PLACEHOLDER_CVC), this);
  cvc_input_->set_default_width_in_chars(8);
  input_row_->AddChildView(cvc_input_);

  views::ImageView* cvc_image = new views::ImageView();
  ui::ResourceBundle& rb = ui::ResourceBundle::GetSharedInstance();
  cvc_image->SetImage(rb.GetImageSkiaNamed(controller_->GetCvcImageRid()));
  input_row_->AddChildView(cvc_image);

  error_label_ = new views::Label(base::ASCIIToUTF16(" "));
  error_label_->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  error_label_->SetEnabledColor(kWarningColor);
  error_label_->SetBorder(views::Border::CreateEmptyBorder(3, 0, 5, 0));
  controls_container->AddChildView(error_label_);

  progress_overlay_ = new FadeOutView();
  progress_overlay_->set_fade_everything(true);
  views::BoxLayout* progress_layout =
      new views::BoxLayout(views::BoxLayout::kHorizontal, 0, 0, 5);
  progress_layout->set_cross_axis_alignment(
      views::BoxLayout::CROSS_AXIS_ALIGNMENT_CENTER);
  progress_layout->set_main_axis_alignment(
      views::BoxLayout::MAIN_AXIS_ALIGNMENT_CENTER);
  progress_overlay_->SetLayoutManager(progress_layout);

  progress_overlay_->SetVisible(false);
  AddChildView(progress_overlay_);

  progress_throbber_ = new views::CheckmarkThrobber();
  progress_overlay_->AddChildView(progress_throbber_);

  progress_label_ = new views::Label(l10n_util::GetStringUTF16(
      IDS_AUTOFILL_CARD_UNMASK_VERIFICATION_IN_PROGRESS));
  progress_label_->SetEnabledColor(SkColorSetRGB(0x42, 0x85, 0xF4));
  progress_overlay_->AddChildView(progress_label_);
}
