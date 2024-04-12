  void OnSignalModalDialogEvent(gfx::NativeViewId containing_window) {
    base::AutoLock auto_lock(modal_dialog_event_map_lock_);
    if (modal_dialog_event_map_.count(containing_window))
      modal_dialog_event_map_[containing_window].event->Signal();
  }
