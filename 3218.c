void CastStreamingNativeHandler::StopCastRtpStream(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  CHECK_EQ(1, args.Length());
  CHECK(args[0]->IsInt32());

  const int transport_id = args[0]->ToInt32(args.GetIsolate())->Value();
  CastRtpStream* transport = GetRtpStreamOrThrow(transport_id);
  if (!transport)
    return;
  transport->Stop();
}
