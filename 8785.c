void InspectorNetworkAgent::ShouldForceCORSPreflight(bool* result) {
  if (state_->booleanProperty(NetworkAgentState::kCacheDisabled, false))
    *result = true;
}
