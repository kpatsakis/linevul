void TestFeaturesNativeHandler::GetAPIFeatures(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  scoped_ptr<JSONFeatureProviderSource> source(
      ExtensionsClient::Get()->CreateFeatureProviderSource("api"));
  scoped_ptr<content::V8ValueConverter> converter(
      content::V8ValueConverter::create());
  args.GetReturnValue().Set(
      converter->ToV8Value(&source->dictionary(), context()->v8_context()));
}
