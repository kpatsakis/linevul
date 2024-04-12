GLboolean WebGL2RenderingContextBase::isSync(WebGLSync* sync) {
  if (isContextLost() || !sync)
    return 0;

  return ContextGL()->IsSync(sync->Object());
}
