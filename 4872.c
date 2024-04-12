pp::Buffer_Dev PDFiumEngine::PrintPagesAsRasterPDF(
    const PP_PrintPageNumberRange_Dev* page_ranges, uint32_t page_range_count,
    const PP_PrintSettings_Dev& print_settings) {
  if (!page_range_count)
    return pp::Buffer_Dev();

  if (doc_ && !doc_loader_.IsDocumentComplete())
    return pp::Buffer_Dev();

  FPDF_DOCUMENT output_doc = FPDF_CreateNewDocument();
  if (!output_doc)
    return pp::Buffer_Dev();

  SaveSelectedFormForPrint();

  std::vector<PDFiumPage> pages_to_print;
  std::vector<std::pair<double, double> > source_page_sizes;
  std::vector<uint32_t> page_numbers =
      GetPageNumbersFromPrintPageNumberRange(page_ranges, page_range_count);
  for (uint32_t page_number : page_numbers) {
    FPDF_PAGE pdf_page = FPDF_LoadPage(doc_, page_number);
    double source_page_width = FPDF_GetPageWidth(pdf_page);
    double source_page_height = FPDF_GetPageHeight(pdf_page);
    source_page_sizes.push_back(std::make_pair(source_page_width,
                                               source_page_height));

    int width_in_pixels = ConvertUnit(source_page_width,
                                      kPointsPerInch,
                                      print_settings.dpi);
    int height_in_pixels = ConvertUnit(source_page_height,
                                       kPointsPerInch,
                                       print_settings.dpi);

    pp::Rect rect(width_in_pixels, height_in_pixels);
    pages_to_print.push_back(PDFiumPage(this, page_number, rect, true));
    FPDF_ClosePage(pdf_page);
  }

#if defined(OS_LINUX)
  g_last_instance_id = client_->GetPluginInstance()->pp_instance();
#endif

  size_t i = 0;
  for (; i < pages_to_print.size(); ++i) {
    double source_page_width = source_page_sizes[i].first;
    double source_page_height = source_page_sizes[i].second;

    FPDF_DOCUMENT temp_doc = CreateSinglePageRasterPdf(source_page_width,
                                                       source_page_height,
                                                       print_settings,
                                                       &pages_to_print[i]);

    if (!temp_doc)
      break;

    pp::Buffer_Dev buffer = GetFlattenedPrintData(temp_doc);
    FPDF_CloseDocument(temp_doc);

    PDFiumMemBufferFileRead file_read(buffer.data(), buffer.size());
    temp_doc = FPDF_LoadCustomDocument(&file_read, nullptr);

    FPDF_BOOL imported = FPDF_ImportPages(output_doc, temp_doc, "1", i);
    FPDF_CloseDocument(temp_doc);
    if (!imported)
      break;
  }

  pp::Buffer_Dev buffer;
  if (i == pages_to_print.size()) {
    FPDF_CopyViewerPreferences(output_doc, doc_);
    FitContentsToPrintableAreaIfRequired(output_doc, print_settings);
    buffer = GetFlattenedPrintData(output_doc);
  }
  FPDF_CloseDocument(output_doc);
  return buffer;
}
