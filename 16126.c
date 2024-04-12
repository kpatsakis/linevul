  static v8::Handle<v8::Value> StartRequest(const v8::Arguments& args) {
    std::string str_args = *v8::String::Utf8Value(args[1]);
    base::JSONReader reader;
    scoped_ptr<Value> value_args;
    value_args.reset(reader.JsonToValue(str_args, false, false));

    if (!value_args.get() || !value_args->IsType(Value::TYPE_LIST)) {
      NOTREACHED() << "Invalid JSON passed to StartRequest.";
      return v8::Undefined();
    }

    return StartRequestCommon(args, static_cast<ListValue*>(value_args.get()));
  }
