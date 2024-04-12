TaskManagerView::TaskManagerView(bool highlight_background_resources)
    : purge_memory_button_(NULL),
      task_manager_(TaskManager::GetInstance()),
      model_(TaskManager::GetInstance()->model()),
      is_always_on_top_(false),
      highlight_background_resources_(highlight_background_resources) {
  Init();
}
