void AutofillPopupItemView::AddSpacerWithSize(int spacer_width,
                                              bool resize,
                                              views::BoxLayout* layout) {
  auto* spacer = new views::View;
  spacer->SetPreferredSize(gfx::Size(spacer_width, 1));
  AddChildView(spacer);
  layout->SetFlexForView(spacer,
                         /*flex=*/resize ? 1 : 0,
                         /*use_min_size=*/true);
}
