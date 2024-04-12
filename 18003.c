RenderMediaClient* RenderMediaClient::GetInstance() {
  static RenderMediaClient* client = new RenderMediaClient();
  return client;
}
