void V8TestObject::installPerContextEnabledMethods(v8::Handle<v8::Object> prototypeTemplate, v8::Isolate* isolate)
{
    v8::Local<v8::Signature> defaultSignature = v8::Signature::New(isolate, domTemplate(isolate));

    ExecutionContext* context = toExecutionContext(prototypeTemplate->CreationContext());
    if (context && context->isDocument() && ContextFeatures::featureNameEnabled(toDocument(context)))
        prototypeTemplate->Set(v8AtomicString(isolate, "enabledPerContextMethod"), v8::FunctionTemplate::New(isolate, TestObjectV8Internal::enabledPerContextMethodMethodCallback, v8Undefined(), defaultSignature, 1)->GetFunction());
}
