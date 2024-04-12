PrintDialogGtk::~PrintDialogGtk() {
  DCHECK(BrowserThread::CurrentlyOn(BrowserThread::UI));

  if (dialog_) {
    gtk_widget_destroy(dialog_);
    dialog_ = NULL;
  }
  if (gtk_settings_) {
    g_object_unref(gtk_settings_);
    gtk_settings_ = NULL;
  }
  if (page_setup_) {
    g_object_unref(page_setup_);
    page_setup_ = NULL;
  }
  if (printer_) {
    g_object_unref(printer_);
    printer_ = NULL;
  }
}
