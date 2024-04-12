    double getDoubleFromMap(v8::Local<v8::Map> map, const String16& key, double defaultValue)
    {
        v8::Local<v8::String> v8Key = toV8String(m_isolate, key);
        if (!map->Has(m_context, v8Key).FromMaybe(false))
            return defaultValue;
        v8::Local<v8::Value> intValue;
        if (!map->Get(m_context, v8Key).ToLocal(&intValue))
            return defaultValue;
        return intValue.As<v8::Number>()->Value();
    }
