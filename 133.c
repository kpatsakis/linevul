LayoutImageResource* ImageLoader::layoutImageResource() {
  LayoutObject* layoutObject = m_element->layoutObject();

  if (!layoutObject)
    return 0;

  if (layoutObject->isImage() &&
      !static_cast<LayoutImage*>(layoutObject)->isGeneratedContent())
    return toLayoutImage(layoutObject)->imageResource();

  if (layoutObject->isSVGImage())
    return toLayoutSVGImage(layoutObject)->imageResource();

  if (layoutObject->isVideo())
    return toLayoutVideo(layoutObject)->imageResource();

  return 0;
}
