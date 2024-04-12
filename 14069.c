GURL GetDataURLWithContent(const std::string& content) {
  std::string encoded_content;
  base::Base64Encode(content, &encoded_content);
  std::string data_uri_content = "data:text/html;base64," + encoded_content;
  return GURL(data_uri_content);
}
