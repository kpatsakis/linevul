void RenderThread::WidgetRestored() {
  DCHECK_GT(hidden_widget_count_, 0);
  hidden_widget_count_--;
  if (!content::GetContentClient()->renderer()->
          RunIdleHandlerWhenWidgetsHidden()) {
    return;
  }

  idle_timer_.Stop();
}
