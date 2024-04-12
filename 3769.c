void NetworkChangeNotifierMac::SetDynamicStoreNotificationKeys(
    SCDynamicStoreRef store) {
#if defined(OS_IOS)
  NOTREACHED();
#else
  base::ScopedCFTypeRef<CFMutableArrayRef> notification_keys(
      CFArrayCreateMutable(kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks));
  base::ScopedCFTypeRef<CFStringRef> key(
      SCDynamicStoreKeyCreateNetworkGlobalEntity(
          NULL, kSCDynamicStoreDomainState, kSCEntNetInterface));
  CFArrayAppendValue(notification_keys.get(), key.get());
  key.reset(SCDynamicStoreKeyCreateNetworkGlobalEntity(
      NULL, kSCDynamicStoreDomainState, kSCEntNetIPv4));
  CFArrayAppendValue(notification_keys.get(), key.get());
  key.reset(SCDynamicStoreKeyCreateNetworkGlobalEntity(
      NULL, kSCDynamicStoreDomainState, kSCEntNetIPv6));
  CFArrayAppendValue(notification_keys.get(), key.get());

  bool ret = SCDynamicStoreSetNotificationKeys(
      store, notification_keys.get(), NULL);
  CHECK(ret);
#endif  // defined(OS_IOS)
}
