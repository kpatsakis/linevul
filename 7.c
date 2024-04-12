  void DragEnd() {
    resizer_->CompleteDrag();
    resizer_.reset();
  }
