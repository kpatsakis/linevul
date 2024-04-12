std::string TestURLLoader::TestBasicFilePOST() {
  std::string message;

  pp::FileSystem file_system(instance_, PP_FILESYSTEMTYPE_LOCALTEMPORARY);
  int32_t rv = OpenFileSystem(&file_system, &message);
  if (rv != PP_OK)
    return ReportError(message.c_str(), rv);

  pp::FileRef file_ref(file_system, "/file_post_test");
  std::string postdata("postdata");
  rv = PrepareFileForPost(file_ref, postdata, &message);
  if (rv != PP_OK)
    return ReportError(message.c_str(), rv);

  pp::URLRequestInfo request(instance_);
  request.SetURL("/echo");
  request.SetMethod("POST");
  request.AppendFileToBody(file_ref, 0);
  return LoadAndCompareBody(request, postdata);
}
