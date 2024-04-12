void RuntimeCustomBindings::OpenChannelToExtension(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  content::RenderFrame* renderframe = context()->GetRenderFrame();
  if (!renderframe)
    return;

  CHECK_EQ(args.Length(), 3);
  CHECK(args[0]->IsString() && args[1]->IsString() && args[2]->IsBoolean());

  ExtensionMsg_ExternalConnectionInfo info;

  const Extension* extension = context()->extension();
  if (extension && !extension->is_hosted_app())
    info.source_id = extension->id();

  info.target_id = *v8::String::Utf8Value(args[0]);
  info.source_url = context()->url();
  std::string channel_name = *v8::String::Utf8Value(args[1]);
  bool include_tls_channel_id =
      args.Length() > 2 ? args[2]->BooleanValue() : false;
  int port_id = -1;
  renderframe->Send(new ExtensionHostMsg_OpenChannelToExtension(
      renderframe->GetRoutingID(), info, channel_name, include_tls_channel_id,
      &port_id));
  args.GetReturnValue().Set(static_cast<int32_t>(port_id));
}
