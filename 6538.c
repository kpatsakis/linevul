void CastStreamingNativeHandler::GetSupportedParamsCastRtpStream(
    const v8::FunctionCallbackInfo<v8::Value>& args) const {
  CHECK_EQ(1, args.Length());
  CHECK(args[0]->IsInt32());

  const int transport_id = args[0]->ToInt32(args.GetIsolate())->Value();
  CastRtpStream* transport = GetRtpStreamOrThrow(transport_id);
  if (!transport)
    return;

  scoped_ptr<V8ValueConverter> converter(V8ValueConverter::create());
  std::vector<CastRtpParams> cast_params = transport->GetSupportedParams();
  v8::Local<v8::Array> result =
      v8::Array::New(args.GetIsolate(),
                     static_cast<int>(cast_params.size()));
  for (size_t i = 0; i < cast_params.size(); ++i) {
    RtpParams params;
    FromCastRtpParams(cast_params[i], &params);
    scoped_ptr<base::DictionaryValue> params_value = params.ToValue();
    result->Set(
        static_cast<int>(i),
        converter->ToV8Value(params_value.get(), context()->v8_context()));
  }
  args.GetReturnValue().Set(result);
}
