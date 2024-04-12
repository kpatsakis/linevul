void GetHostedDocumentURLBlockingThread(const FilePath& gdata_cache_path,
                                        GURL* url) {
  std::string json;
  if (!file_util::ReadFileToString(gdata_cache_path, &json)) {
    NOTREACHED() << "Unable to read file " << gdata_cache_path.value();
    return;
  }
  DVLOG(1) << "Hosted doc content " << json;
  scoped_ptr<base::Value> val(base::JSONReader::Read(json));
  base::DictionaryValue* dict_val;
  if (!val.get() || !val->GetAsDictionary(&dict_val)) {
    NOTREACHED() << "Parse failure for " << json;
    return;
  }
  std::string edit_url;
  if (!dict_val->GetString("url", &edit_url)) {
    NOTREACHED() << "url field doesn't exist in " << json;
    return;
  }
  *url = GURL(edit_url);
  DVLOG(1) << "edit url " << *url;
}
