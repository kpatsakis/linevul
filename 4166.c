AutofillDialogViews::AutofillDialogViews(AutofillDialogViewDelegate* delegate)
    : delegate_(delegate),
      updates_scope_(0),
      needs_update_(false),
      window_(NULL),
      notification_area_(NULL),
      account_chooser_(NULL),
      sign_in_web_view_(NULL),
      scrollable_area_(NULL),
      details_container_(NULL),
      loading_shield_(NULL),
      loading_shield_height_(0),
      overlay_view_(NULL),
      button_strip_extra_view_(NULL),
      save_in_chrome_checkbox_(NULL),
      save_in_chrome_checkbox_container_(NULL),
      button_strip_image_(NULL),
      footnote_view_(NULL),
      legal_document_view_(NULL),
      focus_manager_(NULL),
      error_bubble_(NULL),
      observer_(this) {
  DCHECK(delegate);
  detail_groups_.insert(std::make_pair(SECTION_CC,
                                       DetailsGroup(SECTION_CC)));
  detail_groups_.insert(std::make_pair(SECTION_BILLING,
                                       DetailsGroup(SECTION_BILLING)));
  detail_groups_.insert(std::make_pair(SECTION_CC_BILLING,
                                       DetailsGroup(SECTION_CC_BILLING)));
  detail_groups_.insert(std::make_pair(SECTION_SHIPPING,
                                       DetailsGroup(SECTION_SHIPPING)));
}
