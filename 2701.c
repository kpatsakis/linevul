void TrayCast::UpdatePrimaryView() {
  if (HasCastExtension() == false) {
    if (default_)
      default_->SetVisible(false);
    if (tray_) {
      base::MessageLoopForUI::current()->PostTask(
          FROM_HERE, base::Bind(&tray::CastTrayView::SetVisible,
                                tray_->AsWeakPtr(), false));
    }
  } else {
    if (default_) {
      if (is_casting_)
        default_->ActivateCastView();
      else
        default_->ActivateSelectView();
    }

    if (tray_)
      tray_->SetVisible(is_casting_);
  }
}
