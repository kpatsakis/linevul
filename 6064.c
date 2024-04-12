bool DevToolsClient::isUnderTest() {
  return RenderThreadImpl::current()->layout_test_mode();
}
