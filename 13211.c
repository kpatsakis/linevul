void ChromotingInstance::InjectClipboardEvent(
    const protocol::ClipboardEvent& event) {
  scoped_ptr<base::DictionaryValue> data(new base::DictionaryValue());
  data->SetString("mimeType", event.mime_type());
  data->SetString("item", event.data());
  PostLegacyJsonMessage("injectClipboardItem", data.Pass());
}
