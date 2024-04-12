RenderFrameHostImpl::BuildNavigationClientCommitNavigationCallback(
    NavigationRequest* navigation_request) {
  DCHECK(navigation_request);
  return base::BindOnce(
      &RenderFrameHostImpl::DidCommitPerNavigationMojoInterfaceNavigation,
      base::Unretained(this), navigation_request);
}
