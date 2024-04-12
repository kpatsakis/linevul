 void BrowserEventRouter::DispatchEvent(
    Profile* profile,
    const char* event_name,
    scoped_ptr<ListValue> args,
    EventRouter::UserGestureState user_gesture) {
  if (!profile_->IsSameProfile(profile) ||
      !extensions::ExtensionSystem::Get(profile)->event_router())
    return;

  scoped_ptr<Event> event(new Event(event_name, args.Pass()));
  event->restrict_to_profile = profile;
  event->user_gesture = user_gesture;
  ExtensionSystem::Get(profile)->event_router()->BroadcastEvent(event.Pass());
}
