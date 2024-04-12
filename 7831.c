void Instance::OnControlTimerFired(int32_t,
                                   const uint32& control_id,
                                   const uint32& timer_id) {
  if (control_id == toolbar_->id()) {
    toolbar_->OnTimerFired(timer_id);
  } else if (control_id == progress_bar_.id()) {
    if (timer_id == delayed_progress_timer_id_) {
      if (document_load_state_ == LOAD_STATE_LOADING &&
          !progress_bar_.visible()) {
        progress_bar_.Fade(true, kProgressFadeTimeoutMs);
      }
      delayed_progress_timer_id_ = 0;
    } else {
      progress_bar_.OnTimerFired(timer_id);
    }
  } else if (control_id == kAutoScrollId) {
    if (is_autoscroll_) {
      if (autoscroll_x_ != 0 && h_scrollbar_.get()) {
        h_scrollbar_->ScrollBy(PP_SCROLLBY_PIXEL, autoscroll_x_);
      }
      if (autoscroll_y_ != 0 && v_scrollbar_.get()) {
        v_scrollbar_->ScrollBy(PP_SCROLLBY_PIXEL, autoscroll_y_);
      }

      ScheduleTimer(kAutoScrollId, kAutoScrollTimeoutMs);
    }
  } else if (control_id == kPageIndicatorId) {
    page_indicator_.OnTimerFired(timer_id);
  }
#ifdef ENABLE_THUMBNAILS
  else if (control_id == thumbnails_.id()) {
    thumbnails_.OnTimerFired(timer_id);
  }
#endif
}
