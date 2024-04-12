void BrowserEventRouter::DispatchEvent(
    Profile* profile,
    const char* event_name,
    scoped_ptr<ListValue> args,
    EventRouter::UserGestureState user_gesture) {
  if (!profile_->IsSameProfile(profile) ||
      !extensions::ExtensionSystem::Get(profile)->event_router())
    return;

  extensions::ExtensionSystem::Get(profile)->event_router()->
      DispatchEventToRenderers(event_name, args.Pass(), profile, GURL(),
                               user_gesture);
}
