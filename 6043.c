void Document::PropagateStyleToViewport() {
  DCHECK(InStyleRecalc());
  if (!documentElement())
    return;

  HTMLElement* body = this->body();

  const ComputedStyle* body_style =
      body ? body->EnsureComputedStyle() : nullptr;
  const ComputedStyle* document_element_style =
      documentElement()->EnsureComputedStyle();

  TouchAction effective_touch_action =
      document_element_style->GetEffectiveTouchAction();
  WritingMode root_writing_mode = document_element_style->GetWritingMode();
  TextDirection root_direction = document_element_style->Direction();
  if (body_style) {
    root_writing_mode = body_style->GetWritingMode();
    root_direction = body_style->Direction();
  }

  const ComputedStyle* background_style = document_element_style;
  if (IsHTMLHtmlElement(documentElement()) &&
      document_element_style->Display() != EDisplay::kNone &&
      IsHTMLBodyElement(body) && !background_style->HasBackground()) {
    background_style = body_style;
  }

  Color background_color = Color::kTransparent;
  FillLayer background_layers(EFillLayerType::kBackground, true);
  EImageRendering image_rendering = EImageRendering::kAuto;

  if (background_style->Display() != EDisplay::kNone) {
    background_color = background_style->VisitedDependentColor(
        GetCSSPropertyBackgroundColor());
    background_layers = background_style->BackgroundLayers();
    for (auto* current_layer = &background_layers; current_layer;
         current_layer = current_layer->Next()) {
      current_layer->SetClip(EFillBox::kBorder);

      if (current_layer->Attachment() == EFillAttachment::kScroll)
        current_layer->SetAttachment(EFillAttachment::kLocal);
    }
    image_rendering = background_style->ImageRendering();
  }

  const ComputedStyle* overflow_style = nullptr;
  Element* viewport_element = ViewportDefiningElement();
  DCHECK(viewport_element);
  if (viewport_element == body) {
    overflow_style = body_style;
  } else {
    DCHECK_EQ(viewport_element, documentElement());
    overflow_style = document_element_style;

    if (body_style && !body_style->IsOverflowVisible())
      UseCounter::Count(*this, WebFeature::kBodyScrollsInAdditionToViewport);
  }
  DCHECK(overflow_style);

  EOverflowAnchor overflow_anchor = overflow_style->OverflowAnchor();
  EOverflow overflow_x = overflow_style->OverflowX();
  EOverflow overflow_y = overflow_style->OverflowY();
  if (overflow_x == EOverflow::kVisible)
    overflow_x = EOverflow::kAuto;
  if (overflow_y == EOverflow::kVisible)
    overflow_y = EOverflow::kAuto;
  if (overflow_anchor == EOverflowAnchor::kVisible)
    overflow_anchor = EOverflowAnchor::kAuto;
  GapLength column_gap = overflow_style->ColumnGap();

  ScrollSnapType snap_type = overflow_style->GetScrollSnapType();
  ScrollBehavior scroll_behavior = document_element_style->GetScrollBehavior();

  EOverscrollBehavior overscroll_behavior_x =
      overflow_style->OverscrollBehaviorX();
  EOverscrollBehavior overscroll_behavior_y =
      overflow_style->OverscrollBehaviorY();
  using OverscrollBehaviorType = cc::OverscrollBehavior::OverscrollBehaviorType;
  if (IsInMainFrame()) {
    GetPage()->GetOverscrollController().SetOverscrollBehavior(
        cc::OverscrollBehavior(
            static_cast<OverscrollBehaviorType>(overscroll_behavior_x),
            static_cast<OverscrollBehaviorType>(overscroll_behavior_y)));
  }

  Length scroll_padding_top = overflow_style->ScrollPaddingTop();
  Length scroll_padding_right = overflow_style->ScrollPaddingRight();
  Length scroll_padding_bottom = overflow_style->ScrollPaddingBottom();
  Length scroll_padding_left = overflow_style->ScrollPaddingLeft();

  const ComputedStyle& viewport_style = GetLayoutView()->StyleRef();
  if (viewport_style.GetWritingMode() != root_writing_mode ||
      viewport_style.Direction() != root_direction ||
      viewport_style.VisitedDependentColor(GetCSSPropertyBackgroundColor()) !=
          background_color ||
      viewport_style.BackgroundLayers() != background_layers ||
      viewport_style.ImageRendering() != image_rendering ||
      viewport_style.OverflowAnchor() != overflow_anchor ||
      viewport_style.OverflowX() != overflow_x ||
      viewport_style.OverflowY() != overflow_y ||
      viewport_style.ColumnGap() != column_gap ||
      viewport_style.GetScrollSnapType() != snap_type ||
      viewport_style.GetScrollBehavior() != scroll_behavior ||
      viewport_style.OverscrollBehaviorX() != overscroll_behavior_x ||
      viewport_style.OverscrollBehaviorY() != overscroll_behavior_y ||
      viewport_style.ScrollPaddingTop() != scroll_padding_top ||
      viewport_style.ScrollPaddingRight() != scroll_padding_right ||
      viewport_style.ScrollPaddingBottom() != scroll_padding_bottom ||
      viewport_style.ScrollPaddingLeft() != scroll_padding_left ||
      viewport_style.GetEffectiveTouchAction() != effective_touch_action) {
    scoped_refptr<ComputedStyle> new_style =
        ComputedStyle::Clone(viewport_style);
    new_style->SetWritingMode(root_writing_mode);
    new_style->UpdateFontOrientation();
    new_style->SetDirection(root_direction);
    new_style->SetBackgroundColor(background_color);
    new_style->AccessBackgroundLayers() = background_layers;
    new_style->SetImageRendering(image_rendering);
    new_style->SetOverflowAnchor(overflow_anchor);
    new_style->SetOverflowX(overflow_x);
    new_style->SetOverflowY(overflow_y);
    new_style->SetColumnGap(column_gap);
    new_style->SetScrollSnapType(snap_type);
    new_style->SetScrollBehavior(scroll_behavior);
    new_style->SetOverscrollBehaviorX(overscroll_behavior_x);
    new_style->SetOverscrollBehaviorY(overscroll_behavior_y);
    new_style->SetScrollPaddingTop(scroll_padding_top);
    new_style->SetScrollPaddingRight(scroll_padding_right);
    new_style->SetScrollPaddingBottom(scroll_padding_bottom);
    new_style->SetScrollPaddingLeft(scroll_padding_left);
    new_style->SetEffectiveTouchAction(effective_touch_action);
    GetLayoutView()->SetStyle(new_style);
    SetupFontBuilder(*new_style);

    if (PaintLayerScrollableArea* scrollable_area =
            GetLayoutView()->GetScrollableArea()) {
      if (scrollable_area->HorizontalScrollbar() &&
          scrollable_area->HorizontalScrollbar()->IsCustomScrollbar())
        scrollable_area->HorizontalScrollbar()->StyleChanged();
      if (scrollable_area->VerticalScrollbar() &&
          scrollable_area->VerticalScrollbar()->IsCustomScrollbar())
        scrollable_area->VerticalScrollbar()->StyleChanged();
    }
  }
}
