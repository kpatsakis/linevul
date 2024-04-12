  void ScrollbarOverlayChanged(pp::Scrollbar_Dev scrollbar, bool overlay) {
    if (ppp_scrollbar_ != NULL) {
      ppp_scrollbar_->OverlayChanged(plugin_->pp_instance(),
                                     scrollbar.pp_resource(),
                                     PP_FromBool(overlay));
    }
  }
