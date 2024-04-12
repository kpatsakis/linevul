  explicit ScopedGestureRecognizerSetter(ui::GestureRecognizer* new_gr)
      : new_gr_(new_gr) {
    original_gr_ = ui::GestureRecognizer::Get();
    ui::SetGestureRecognizerForTesting(new_gr_.get());
  }
