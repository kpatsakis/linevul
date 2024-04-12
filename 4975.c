  bool IsUsed(vr::EVRButtonId button_id) {
    auto it = used_axes_.find(button_id);
    return it != used_axes_.end();
  }
