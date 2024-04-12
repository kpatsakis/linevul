void TabStripGtk::SchedulePaint() {
  gtk_widget_queue_draw(tabstrip_.get());
}
