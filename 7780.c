void RenderViewImpl::OnEnumerateDirectoryResponse(
    int id,
    const std::vector<FilePath>& paths) {
  if (!enumeration_completions_[id])
    return;

  WebVector<WebString> ws_file_names(paths.size());
  for (size_t i = 0; i < paths.size(); ++i)
    ws_file_names[i] = webkit_base::FilePathToWebString(paths[i]);

  enumeration_completions_[id]->didChooseFile(ws_file_names);
  enumeration_completions_.erase(id);
}
