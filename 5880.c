void rethrowExceptionInPrivateScript(v8::Isolate* isolate, v8::TryCatch& block, ScriptState* scriptStateInUserScript, ExceptionState::ContextType errorContext, const char* propertyName, const char* interfaceName)
{
    v8::Local<v8::Context> context = scriptStateInUserScript->context();
    v8::Local<v8::Value> exception = block.Exception();
    RELEASE_ASSERT(!exception.IsEmpty() && exception->IsObject());

    v8::Local<v8::Object> exceptionObject = v8::Local<v8::Object>::Cast(exception);
    v8::Local<v8::Value> name = exceptionObject->Get(context, v8String(isolate, "name")).ToLocalChecked();
    RELEASE_ASSERT(name->IsString());

    v8::Local<v8::Message> tryCatchMessage = block.Message();
    v8::Local<v8::Value> message;
    String messageString;
    if (exceptionObject->Get(context, v8String(isolate, "message")).ToLocal(&message) && message->IsString())
        messageString = toCoreString(v8::Local<v8::String>::Cast(message));

    String exceptionName = toCoreString(v8::Local<v8::String>::Cast(name));
    if (exceptionName == "PrivateScriptException") {
        v8::Local<v8::Value> code = exceptionObject->Get(context, v8String(isolate, "code")).ToLocalChecked();
        RELEASE_ASSERT(code->IsInt32());
        int exceptionCode = code.As<v8::Int32>()->Value();
        ScriptState::Scope scope(scriptStateInUserScript);
        ExceptionState exceptionState(errorContext, propertyName, interfaceName, context->Global(), scriptStateInUserScript->isolate());
        exceptionState.throwDOMException(exceptionCode, messageString);
        return;
    }

    if (exceptionName == "RangeError" && messageString.contains("Maximum call stack size exceeded")) {
        ScriptState::Scope scope(scriptStateInUserScript);
        ExceptionState exceptionState(errorContext, propertyName, interfaceName, scriptStateInUserScript->context()->Global(), scriptStateInUserScript->isolate());
        exceptionState.throwDOMException(V8RangeError, messageString);
        return;
    }

    fprintf(stderr, "Private script error: %s was thrown.\n", exceptionName.utf8().data());
    dumpV8Message(context, tryCatchMessage);
    RELEASE_NOTREACHED();
}
