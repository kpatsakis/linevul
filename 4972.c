ContentSecurityPolicy::DirectiveType ContentSecurityPolicy::getDirectiveType(
    const String& name) {
  if (name == "base-uri")
    return DirectiveType::BaseURI;
  if (name == "block-all-mixed-content")
    return DirectiveType::BlockAllMixedContent;
  if (name == "child-src")
    return DirectiveType::ChildSrc;
  if (name == "connect-src")
    return DirectiveType::ConnectSrc;
  if (name == "default-src")
    return DirectiveType::DefaultSrc;
  if (name == "frame-ancestors")
    return DirectiveType::FrameAncestors;
  if (name == "frame-src")
    return DirectiveType::FrameSrc;
  if (name == "font-src")
    return DirectiveType::FontSrc;
  if (name == "form-action")
    return DirectiveType::FormAction;
  if (name == "img-src")
    return DirectiveType::ImgSrc;
  if (name == "manifest-src")
    return DirectiveType::ManifestSrc;
  if (name == "media-src")
    return DirectiveType::MediaSrc;
  if (name == "object-src")
    return DirectiveType::ObjectSrc;
  if (name == "plugin-types")
    return DirectiveType::PluginTypes;
  if (name == "report-uri")
    return DirectiveType::ReportURI;
  if (name == "require-sri-for")
    return DirectiveType::RequireSRIFor;
  if (name == "sandbox")
    return DirectiveType::Sandbox;
  if (name == "script-src")
    return DirectiveType::ScriptSrc;
  if (name == "style-src")
    return DirectiveType::StyleSrc;
  if (name == "treat-as-public-address")
    return DirectiveType::TreatAsPublicAddress;
  if (name == "upgrade-insecure-requests")
    return DirectiveType::UpgradeInsecureRequests;
  if (name == "worker-src")
    return DirectiveType::WorkerSrc;

  return DirectiveType::Undefined;
}
