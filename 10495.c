std::string TestURLLoader::TestFollowURLRedirect() {
  pp::URLRequestInfo request(instance_);
  std::string redirect_prefix("/server-redirect?");
  std::string redirect_url =
      GetReachableAbsoluteURL("test_url_loader_data/hello.txt");
  request.SetURL(redirect_prefix.append(redirect_url));
  return LoadAndCompareBody(request, "hello\n");
}
