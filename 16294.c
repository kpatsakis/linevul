V8HeapStatsObserver::V8HeapStatsObserver(
    AutomationProvider* automation,
    IPC::Message* reply_message,
    base::ProcessId renderer_id)
    : automation_(automation->AsWeakPtr()),
      reply_message_(reply_message),
      renderer_id_(renderer_id) {
  registrar_.Add(
      this,
      chrome::NOTIFICATION_RENDERER_V8_HEAP_STATS_COMPUTED,
      content::NotificationService::AllSources());
}
