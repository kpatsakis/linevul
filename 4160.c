static PassRefPtr<Image> imageFromNode(const Node& node) {
  DCHECK(!node.document().needsLayoutTreeUpdate());
  DocumentLifecycle::DisallowTransitionScope disallowTransition(
      node.document().lifecycle());

  LayoutObject* layoutObject = node.layoutObject();
  if (!layoutObject)
    return nullptr;

  if (layoutObject->isCanvas()) {
    return toHTMLCanvasElement(node).copiedImage(
        FrontBuffer, PreferNoAcceleration, SnapshotReasonCopyToClipboard);
  }

  if (layoutObject->isImage()) {
    LayoutImage* layoutImage = toLayoutImage(layoutObject);
    if (!layoutImage)
      return nullptr;

    ImageResourceContent* cachedImage = layoutImage->cachedImage();
    if (!cachedImage || cachedImage->errorOccurred())
      return nullptr;
    return cachedImage->getImage();
  }

  return nullptr;
}
