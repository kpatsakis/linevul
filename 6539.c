void GetDocumentResourceIdOnBlockingPool(
    const FilePath& local_file_path,
    std::string* resource_id) {
  DCHECK(resource_id);

  if (DocumentEntry::HasHostedDocumentExtension(local_file_path)) {
    std::string error;
    DictionaryValue* dict_value = NULL;
    JSONFileValueSerializer serializer(local_file_path);
    scoped_ptr<Value> value(serializer.Deserialize(NULL, &error));
    if (value.get() && value->GetAsDictionary(&dict_value))
      dict_value->GetString("resource_id", resource_id);
  }
}
