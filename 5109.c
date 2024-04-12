static v8::Persistent<v8::FunctionTemplate> ConfigureV8TestNamedConstructorTemplate(v8::Persistent<v8::FunctionTemplate> desc)
{
    desc->ReadOnlyPrototype();

    v8::Local<v8::Signature> defaultSignature;
    defaultSignature = configureTemplate(desc, "TestNamedConstructor", v8::Persistent<v8::FunctionTemplate>(), V8TestNamedConstructor::internalFieldCount,
        0, 0,
        0, 0);
    UNUSED_PARAM(defaultSignature); // In some cases, it will not be used.
    

    desc->Set(getToStringName(), getToStringTemplate());
    return desc;
}
