printing::PreviewMetafile* PrintWebViewHelper::PrintPreviewContext::metafile() {
  DCHECK(IsRendering());
  return metafile_.get();
}
