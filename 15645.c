views::BubbleBorder* AutofillDialogViews::OverlayView::GetBubbleBorder() {
  views::View* frame = GetWidget()->non_client_view()->frame_view();
  std::string bubble_frame_view_name(views::BubbleFrameView::kViewClassName);
  if (frame->GetClassName() == bubble_frame_view_name)
    return static_cast<views::BubbleFrameView*>(frame)->bubble_border();
  NOTREACHED();
  return NULL;
}
