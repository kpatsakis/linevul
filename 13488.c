void FreeInputMethodNames(GList* engines) {
  if (engines) {
    for (GList* cursor = engines; cursor; cursor = g_list_next(cursor)) {
      g_object_unref(IBUS_ENGINE_DESC(cursor->data));
    }
    g_list_free(engines);
  }
}
