void Notification::dispatchCloseEvent()
{
    if (m_state != NotificationStateShowing && m_state != NotificationStateClosing)
        return;

    m_state = NotificationStateClosed;
    dispatchEvent(Event::create(EventTypeNames::close));
}
