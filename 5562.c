SubstituteData FrameLoader::DefaultSubstituteDataForURL(const KURL& url) {
  if (!ShouldTreatURLAsSrcdocDocument(url))
    return SubstituteData();
  String srcdoc = frame_->DeprecatedLocalOwner()->FastGetAttribute(srcdocAttr);
  DCHECK(!srcdoc.IsNull());
  CString encoded_srcdoc = srcdoc.Utf8();
  return SubstituteData(
      SharedBuffer::Create(encoded_srcdoc.data(), encoded_srcdoc.length()),
      "text/html", "UTF-8", NullURL());
}
