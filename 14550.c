void ClipboardMessageFilter::OnWriteObjectsAsync(
    const ui::Clipboard::ObjectMap& objects) {
  ui::Clipboard::ObjectMap* long_living_objects =
      new ui::Clipboard::ObjectMap(objects);

  long_living_objects->erase(ui::Clipboard::CBF_SMBITMAP);

  BrowserThread::PostTask(
      BrowserThread::UI,
      FROM_HERE,
      new WriteClipboardTask(long_living_objects));
}
