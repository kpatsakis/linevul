std::vector<pp::ImageData> Instance::GetThumbnailResources() {
  std::vector<pp::ImageData> num_images(10);
  num_images[0] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_0);
  num_images[1] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_1);
  num_images[2] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_2);
  num_images[3] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_3);
  num_images[4] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_4);
  num_images[5] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_5);
  num_images[6] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_6);
  num_images[7] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_7);
  num_images[8] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_8);
  num_images[9] = CreateResourceImage(PP_RESOURCEIMAGE_PDF_BUTTON_THUMBNAIL_9);
  return num_images;
}
