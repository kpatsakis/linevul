    void writeRegExp(v8::Local<v8::String> pattern, v8::RegExp::Flags flags)
    {
        append(RegExpTag);
        v8::String::Utf8Value patternUtf8Value(pattern);
        doWriteString(*patternUtf8Value, patternUtf8Value.length());
        doWriteUint32(static_cast<uint32_t>(flags));
    }
