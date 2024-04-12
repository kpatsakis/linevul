std::unique_ptr<NavigationState> NavigationState::CreateContentInitiated() {
  return base::WrapUnique(new NavigationState(
      CommonNavigationParams(), CommitNavigationParams(), base::TimeTicks(),
      true, content::mojom::FrameNavigationControl::CommitNavigationCallback(),
      content::mojom::NavigationClient::CommitNavigationCallback(), nullptr,
      true));
}
