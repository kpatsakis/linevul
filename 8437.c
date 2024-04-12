void WebLocalFrameImpl::SetIsolatedWorldSecurityOrigin(
    int world_id,
    const WebSecurityOrigin& security_origin) {
  DCHECK(GetFrame());
  DOMWrapperWorld::SetIsolatedWorldSecurityOrigin(
      world_id,
      security_origin.Get() ? security_origin.Get()->IsolatedCopy() : nullptr);
}
