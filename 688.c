void BrightnessObserver::BrightnessChanged(int level, bool user_initiated) {
  if (user_initiated)
    BrightnessBubble::GetInstance()->ShowBubble(level, true);
  else
    BrightnessBubble::GetInstance()->UpdateWithoutShowingBubble(level, true);

  VolumeBubble::GetInstance()->HideBubble();
}
