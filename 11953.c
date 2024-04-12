bool RenderFrameHostImpl::SchemeShouldBypassCSP(
    const base::StringPiece& scheme) {
  const auto& bypassing_schemes = url::GetCSPBypassingSchemes();
  return base::ContainsValue(bypassing_schemes, scheme);
}
