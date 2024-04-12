ScriptValue WebGLRenderingContextBase::getExtension(ScriptState* script_state,
                                                    const String& name) {
  WebGLExtension* extension = nullptr;

  if (name == WebGLDebugRendererInfo::ExtensionName()) {
    ExecutionContext* context = ExecutionContext::From(script_state);
    UseCounter::Count(context, WebFeature::kWebGLDebugRendererInfo);
    Dactyloscoper::Record(context, WebFeature::kWebGLDebugRendererInfo);
  }

  if (!isContextLost()) {
    for (ExtensionTracker* tracker : extensions_) {
      if (tracker->MatchesNameWithPrefixes(name)) {
        if (ExtensionSupportedAndAllowed(tracker)) {
          extension = tracker->GetExtension(this);
          if (extension) {
            if (!extension_enabled_[extension->GetName()]) {
              extension_enabled_[extension->GetName()] = true;
            }
          }
        }
        break;
      }
    }
  }

  v8::Local<v8::Value> wrapped_extension =
      ToV8(extension, script_state->GetContext()->Global(),
           script_state->GetIsolate());

  return ScriptValue(script_state, wrapped_extension);
}
