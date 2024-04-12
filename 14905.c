ScreenLayoutObserverTest::GetDisplayNotification() const {
  const message_center::NotificationList::Notifications notifications =
      message_center::MessageCenter::Get()->GetVisibleNotifications();
  for (const auto* notification : notifications) {
    if (notification->id() == ScreenLayoutObserver::kNotificationId)
      return notification;
  }

  return nullptr;
}
