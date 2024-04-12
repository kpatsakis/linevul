void Document::UpdateStyleAndLayoutIgnorePendingStylesheets(
    Document::RunPostLayoutTasks run_post_layout_tasks) {
  UpdateStyleAndLayoutTreeIgnorePendingStylesheets();
  UpdateStyleAndLayout();

  if (run_post_layout_tasks == kRunPostLayoutTasksSynchronously && View())
    View()->FlushAnyPendingPostLayoutTasks();
  ++force_layout_count_;
}
