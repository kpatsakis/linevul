  explicit TestWindowObserver(aura::Window* window_to_observe)
      : window_(window_to_observe) {
    window_->AddObserver(this);
  }
