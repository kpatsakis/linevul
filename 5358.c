 void PrintDialogGtk::OnResponse(gint response_id) {
  gtk_widget_hide(dialog_);

  switch (response_id) {
    case GTK_RESPONSE_OK: {
      GtkPrinter* printer =
          gtk_print_unix_dialog_get_selected_printer(
              GTK_PRINT_UNIX_DIALOG(dialog_));
      if (!gtk_printer_accepts_pdf(printer)) {
        browser_->GetSelectedTabContents()->AddInfoBar(
            new PdfUnsupportedInfoBarDelegate(browser_));
        break;
      }

      GtkPrintSettings* settings =
          gtk_print_unix_dialog_get_settings(
              GTK_PRINT_UNIX_DIALOG(dialog_));
      GtkPageSetup* setup = gtk_print_unix_dialog_get_page_setup(
              GTK_PRINT_UNIX_DIALOG(dialog_));

      GtkPrintJob* job =
          gtk_print_job_new(path_to_pdf_.value().c_str(), printer,
                            settings, setup);
      gtk_print_job_set_source_file(job, path_to_pdf_.value().c_str(), NULL);
      gtk_print_job_send(job, OnJobCompletedThunk, this, NULL);
      g_object_unref(settings);
      return;
    }
    case GTK_RESPONSE_DELETE_EVENT:  // Fall through.
    case GTK_RESPONSE_CANCEL: {
      break;
    }
    case GTK_RESPONSE_APPLY:
    default: {
      NOTREACHED();
    }
  }

  OnJobCompleted(NULL, NULL);
}
