PermissionsBubbleDialogDelegateView::PermissionsBubbleDialogDelegateView(
    PermissionPromptImpl* owner,
    const std::vector<PermissionRequest*>& requests)
    : owner_(owner), persist_checkbox_(nullptr) {
  DCHECK(!requests.empty());

  set_close_on_deactivate(false);
  set_arrow(kPermissionAnchorArrow);

#if defined(OS_MACOSX)
  if (base::FeatureList::IsEnabled(features::kMacRTL))
    set_mirror_arrow_in_rtl(true);
#endif

  ChromeLayoutProvider* provider = ChromeLayoutProvider::Get();
  SetLayoutManager(new views::BoxLayout(
      views::BoxLayout::kVertical, gfx::Insets(),
      provider->GetDistanceMetric(views::DISTANCE_RELATED_CONTROL_VERTICAL)));

  display_origin_ = url_formatter::FormatUrlForSecurityDisplay(
      requests[0]->GetOrigin(),
      url_formatter::SchemeDisplay::OMIT_CRYPTOGRAPHIC);

  bool show_persistence_toggle = true;
  for (size_t index = 0; index < requests.size(); index++) {
    views::View* label_container = new views::View();
    int indent =
        provider->GetDistanceMetric(DISTANCE_SUBSECTION_HORIZONTAL_INDENT);
    label_container->SetLayoutManager(new views::BoxLayout(
        views::BoxLayout::kHorizontal, gfx::Insets(0, indent),
        provider->GetDistanceMetric(views::DISTANCE_RELATED_LABEL_HORIZONTAL)));
    views::ImageView* icon = new views::ImageView();
    const gfx::VectorIcon& vector_id = requests[index]->GetIconId();
    icon->SetImage(
        gfx::CreateVectorIcon(vector_id, kIconSize, gfx::kChromeIconGrey));
    icon->SetTooltipText(base::string16());  // Redundant with the text fragment
    label_container->AddChildView(icon);
    views::Label* label =
        new views::Label(requests.at(index)->GetMessageTextFragment());
    label->SetHorizontalAlignment(gfx::ALIGN_LEFT);
    label_container->AddChildView(label);
    AddChildView(label_container);

    show_persistence_toggle = show_persistence_toggle &&
                              requests[index]->ShouldShowPersistenceToggle();
  }

  if (show_persistence_toggle) {
    persist_checkbox_ = new views::Checkbox(
        l10n_util::GetStringUTF16(IDS_PERMISSIONS_BUBBLE_PERSIST_TEXT));
    persist_checkbox_->SetHorizontalAlignment(gfx::ALIGN_LEFT);
    persist_checkbox_->SetChecked(true);
    AddChildView(persist_checkbox_);
  }
  chrome::RecordDialogCreation(chrome::DialogIdentifier::PERMISSIONS);
}
