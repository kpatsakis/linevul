bool AXObject::lastKnownIsIgnoredValue() {
  if (m_lastKnownIsIgnoredValue == DefaultBehavior)
    m_lastKnownIsIgnoredValue =
        accessibilityIsIgnored() ? IgnoreObject : IncludeObject;

  return m_lastKnownIsIgnoredValue == IgnoreObject;
}
