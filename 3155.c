void ImageInputType::srcAttributeChanged()
{
    if (!element().layoutObject())
        return;
    element().ensureImageLoader().updateFromElement(ImageLoader::UpdateIgnorePreviousError);
}
