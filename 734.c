    void reportCallWithArgument(ConsoleAPIType type, const String16& message)
    {
        std::vector<v8::Local<v8::Value>> arguments(1, toV8String(m_isolate, message));
        reportCall(type, arguments);
    }
