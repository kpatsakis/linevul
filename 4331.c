EditorClient& Editor::client() const {
  if (Page* page = frame().page())
    return page->editorClient();
  return emptyEditorClient();
}
