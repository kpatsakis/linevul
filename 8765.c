void LoginDisplayHostWebUI::TryToPlayOobeStartupSound() {
  if (is_voice_interaction_oobe_)
    return;

  if (oobe_startup_sound_played_ || login_prompt_visible_time_.is_null() ||
      !CrasAudioHandler::Get()->GetPrimaryActiveOutputNode()) {
    return;
  }

  oobe_startup_sound_played_ = true;

  if (base::TimeTicks::Now() - login_prompt_visible_time_ >
      base::TimeDelta::FromMilliseconds(kStartupSoundMaxDelayMs)) {
    return;
  }

  AccessibilityManager::Get()->PlayEarcon(SOUND_STARTUP,
                                          PlaySoundOption::ALWAYS);
}
