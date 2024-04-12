int32_t TestURLLoader::OpenWithPrefetchBufferThreshold(int32_t lower,
                                                       int32_t upper) {
  pp::URLRequestInfo request(instance_);
  request.SetURL("test_url_loader_data/hello.txt");
  request.SetPrefetchBufferLowerThreshold(lower);
  request.SetPrefetchBufferUpperThreshold(upper);

  return OpenUntrusted(request, NULL);
}
