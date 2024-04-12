bool IsHttpPost(const blink::WebURLRequest& request) {
  return request.HttpMethod().Utf8() == "POST";
}
