static v8::Handle<v8::Value> withScriptStateObjExceptionCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.TestObj.withScriptStateObjException");
    TestObj* imp = V8TestObj::toNative(args.Holder());
    ExceptionCode ec = 0;
    {
    EmptyScriptState state;
    RefPtr<TestObj> result = imp->withScriptStateObjException(&state, ec);
    if (UNLIKELY(ec))
        goto fail;
    if (state.hadException())
        return throwError(state.exception(), args.GetIsolate());
    return toV8(result.release(), args.GetIsolate());
    }
    fail:
    V8Proxy::setDOMException(ec, args.GetIsolate());
    return v8::Handle<v8::Value>();
}
