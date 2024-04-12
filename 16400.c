bool RenderFrameHostManager::ShouldTransitionCrossSite() {
  return !base::CommandLine::ForCurrentProcess()->HasSwitch(
      switches::kSingleProcess);
}
