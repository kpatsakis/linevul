 void PageCaptureCustomBindings::CreateBlob(
    const v8::FunctionCallbackInfo<v8::Value>& args) {
  CHECK(args.Length() == 2);
  CHECK(args[0]->IsString());
  CHECK(args[1]->IsInt32());
  blink::WebString path(base::UTF8ToUTF16(*v8::String::Utf8Value(args[0])));
  blink::WebBlob blob =
      blink::WebBlob::createFromFile(path, args[1]->Int32Value());
  args.GetReturnValue().Set(
      blob.toV8Value(context()->v8_context()->Global(), args.GetIsolate()));
}
