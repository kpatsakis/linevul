MessageService::MessageService(
    LazyBackgroundTaskQueue* queue)
    : lazy_background_task_queue_(queue),
      weak_factory_(this) {
  registrar_.Add(this, content::NOTIFICATION_RENDERER_PROCESS_TERMINATED,
                 content::NotificationService::AllBrowserContextsAndSources());
  registrar_.Add(this, content::NOTIFICATION_RENDERER_PROCESS_CLOSED,
                 content::NotificationService::AllBrowserContextsAndSources());
}
