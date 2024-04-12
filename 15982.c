v8::Handle<v8::Value> V8WebGLRenderingContext::getVertexAttribCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.WebGLRenderingContext.getVertexAttrib()");
    return getObjectParameter(args, kVertexAttrib);
}
