void PDFiumEngine::FinishPaint(int progressive_index,
                               pp::ImageData* image_data) {
  DCHECK_GE(progressive_index, 0);
  DCHECK_LT(static_cast<size_t>(progressive_index), progressive_paints_.size());
  DCHECK(image_data);

  int page_index = progressive_paints_[progressive_index].page_index;
  const pp::Rect& dirty_in_screen = progressive_paints_[progressive_index].rect;
  FPDF_BITMAP bitmap = progressive_paints_[progressive_index].bitmap;
  int start_x, start_y, size_x, size_y;
  GetPDFiumRect(page_index, dirty_in_screen, &start_x, &start_y, &size_x,
                &size_y);

  FPDF_FFLDraw(form_, bitmap, pages_[page_index]->GetPage(), start_x, start_y,
               size_x, size_y, current_rotation_, GetRenderingFlags());

  FillPageSides(progressive_index);

  PaintPageShadow(progressive_index, image_data);

  DrawSelections(progressive_index, image_data);

  FPDF_RenderPage_Close(pages_[page_index]->GetPage());
  FPDFBitmap_Destroy(bitmap);
  progressive_paints_.erase(progressive_paints_.begin() + progressive_index);

  client_->DocumentPaintOccurred();
}
