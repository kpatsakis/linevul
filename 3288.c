PrintDialogGtk::PrintDialogGtk(PrintingContextCairo* context)
    : callback_(NULL),
      context_(context),
      dialog_(NULL),
      gtk_settings_(NULL),
      page_setup_(NULL),
      printer_(NULL) {
}
