void Browser::Print() {
  if (switches::IsPrintPreviewEnabled())
    GetSelectedTabContentsWrapper()->print_view_manager()->PrintPreviewNow();
  else
    GetSelectedTabContentsWrapper()->print_view_manager()->PrintNow();
}
