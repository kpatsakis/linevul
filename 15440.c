void WebContentsImpl::OnEndColorChooser(int color_chooser_id) {
  if (color_chooser_info_ &&
      color_chooser_id == color_chooser_info_->identifier)
    color_chooser_info_->chooser->End();
}
