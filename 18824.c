v8::Handle<v8::Value> V8WebGLRenderingContext::uniform2fvCallback(const v8::Arguments& args)
{
    INC_STATS("DOM.WebGLRenderingContext.uniform2fv()");
    return vertexAttribAndUniformHelperf(args, kUniform2v);
}
