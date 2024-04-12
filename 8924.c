std::string TestURLLoader::TestEmptyDataPOST() {
  pp::URLRequestInfo request(instance_);
  request.SetURL("/echo");
  request.SetMethod("POST");
  request.AppendDataToBody("", 0);
  return LoadAndCompareBody(request, std::string());
}
