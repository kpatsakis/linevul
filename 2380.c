void CastCastView::UpdateLabel() {
  if (cast_config_delegate_ == nullptr ||
      cast_config_delegate_->HasCastExtension() == false)
    return;

  cast_config_delegate_->GetReceiversAndActivities(
      base::Bind(&CastCastView::UpdateLabelCallback, base::Unretained(this)));
}
