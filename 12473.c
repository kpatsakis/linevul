void PrintPreviewHandler::HandlePrintToPdf(
    const base::DictionaryValue& settings) {
  PrintPreviewUI* print_preview_ui = static_cast<PrintPreviewUI*>(
      web_ui()->GetController());
  if (print_to_pdf_path_.get()) {
    scoped_refptr<base::RefCountedBytes> data;
    print_preview_ui->GetPrintPreviewDataForIndex(
        printing::COMPLETE_PREVIEW_DOCUMENT_INDEX, &data);
    PostPrintToPdfTask(data);
  } else if (!select_file_dialog_.get() || !select_file_dialog_->IsRunning(
        platform_util::GetTopLevel(preview_web_contents()->GetNativeView()))) {
    ReportUserActionHistogram(PRINT_TO_PDF);
    UMA_HISTOGRAM_COUNTS("PrintPreview.PageCount.PrintToPDF",
                         GetPageCountFromSettingsDictionary(settings));

    string16 print_job_title_utf16 = print_preview_ui->initiator_tab_title();

#if defined(OS_WIN)
    FilePath::StringType print_job_title(print_job_title_utf16);
#elif defined(OS_POSIX)
    FilePath::StringType print_job_title = UTF16ToUTF8(print_job_title_utf16);
#endif

    file_util::ReplaceIllegalCharactersInPath(&print_job_title, '_');
    FilePath default_filename(print_job_title);
    default_filename =
        default_filename.ReplaceExtension(FILE_PATH_LITERAL("pdf"));

    SelectFile(default_filename);
  }
}
