  void VerifyPrintPreviewInvalidPrinterSettings(bool settings_invalid) {
    bool print_preview_invalid_printer_settings =
        (render_thread_->sink().GetUniqueMessageMatching(
            PrintHostMsg_PrintPreviewInvalidPrinterSettings::ID) != NULL);
    EXPECT_EQ(settings_invalid, print_preview_invalid_printer_settings);
  }
