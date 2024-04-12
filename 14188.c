void LocalFrame::SetPrinting(bool printing,
                             bool use_printing_layout,
                             const FloatSize& page_size,
                             const FloatSize& original_page_size,
                             float maximum_shrink_ratio) {
  ResourceCacheValidationSuppressor validation_suppressor(
      GetDocument()->Fetcher());

  GetDocument()->SetPrinting(printing ? Document::kPrinting
                                      : Document::kFinishingPrinting);
  View()->AdjustMediaTypeForPrinting(printing);

  if (TextAutosizer* text_autosizer = GetDocument()->GetTextAutosizer())
    text_autosizer->UpdatePageInfo();

  if (use_printing_layout && ShouldUsePrintingLayout()) {
    View()->ForceLayoutForPagination(page_size, original_page_size,
                                     maximum_shrink_ratio);
  } else {
    if (LayoutView* layout_view = View()->GetLayoutView()) {
      layout_view->SetPreferredLogicalWidthsDirty();
      layout_view->SetNeedsLayout(LayoutInvalidationReason::kPrintingChanged);
      layout_view->SetShouldDoFullPaintInvalidationForViewAndAllDescendants();
    }
    View()->UpdateLayout();
    View()->AdjustViewSize();
  }

  for (Frame* child = Tree().FirstChild(); child;
       child = child->Tree().NextSibling()) {
    if (child->IsLocalFrame()) {
      if (printing)
        ToLocalFrame(child)->StartPrintingWithoutPrintingLayout();
      else
        ToLocalFrame(child)->EndPrinting();
    }
  }

  View()->SetSubtreeNeedsPaintPropertyUpdate();

  if (!printing)
    GetDocument()->SetPrinting(Document::kNotPrinting);
}
