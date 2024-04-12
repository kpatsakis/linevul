gboolean Shell::OnWindowDestroyed(GtkWidget* window) {
  delete this;
  return FALSE;  // Don't stop this message.
}
