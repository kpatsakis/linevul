void PDFiumEngine::DeviceToPage(int page_index,
                                float device_x,
                                float device_y,
                                double* page_x,
                                double* page_y) {
  *page_x = *page_y = 0;
  int temp_x = static_cast<int>((device_x + position_.x()) / current_zoom_ -
      pages_[page_index]->rect().x());
  int temp_y = static_cast<int>((device_y + position_.y()) / current_zoom_ -
      pages_[page_index]->rect().y());
  FPDF_DeviceToPage(
      pages_[page_index]->GetPage(), 0, 0,
      pages_[page_index]->rect().width(),  pages_[page_index]->rect().height(),
      current_rotation_, temp_x, temp_y, page_x, page_y);
}
