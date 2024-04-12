bool roleAllowsOrientation(AccessibilityRole role) {
  return role == ScrollBarRole || role == SplitterRole || role == SliderRole;
}
