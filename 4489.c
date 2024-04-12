blink::UserAgentMetadata GetUserAgentMetadata() {
  blink::UserAgentMetadata metadata;

  metadata.brand = version_info::GetProductName();
  metadata.full_version = version_info::GetVersionNumber();
  metadata.major_version = version_info::GetMajorVersionNumber();
  metadata.platform = version_info::GetOSType();

  metadata.architecture = "";
  metadata.model = "";

  return metadata;
}
