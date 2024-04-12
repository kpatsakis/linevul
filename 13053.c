void TouchEventHandler::playSoundIfAnchorIsTarget() const
{
    if (m_lastFatFingersResult.node() && m_lastFatFingersResult.node()->isLink())
        BlackBerry::Platform::SystemSound::instance()->playSound(BlackBerry::Platform::SystemSoundType::InputKeypress);
}
