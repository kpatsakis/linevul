std::unique_ptr<NavigationThrottle> NetworkHandler::CreateThrottleForNavigation(
    NavigationHandle* navigation_handle) {
  if (!interception_handle_)
    return nullptr;
  std::unique_ptr<NavigationThrottle> throttle(new NetworkNavigationThrottle(
      weak_factory_.GetWeakPtr(), navigation_handle));
  return throttle;
}
