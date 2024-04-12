void InspectorPageAgent::Did(const probe::UpdateLayout&) {
  PageLayoutInvalidated(false);
}
