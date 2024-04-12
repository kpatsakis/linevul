void CastSelectDefaultView::UpdateLabel() {
  if (cast_config_delegate_ == nullptr ||
      cast_config_delegate_->HasCastExtension() == false)
    return;

  cast_config_delegate_->GetReceiversAndActivities(base::Bind(
      &CastSelectDefaultView::UpdateLabelCallback, base::Unretained(this)));
}
