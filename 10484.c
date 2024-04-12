void WasmResponseExtensions::Initialize(v8::Isolate* isolate) {
  if (RuntimeEnabledFeatures::WebAssemblyStreamingEnabled()) {
    isolate->SetWasmCompileStreamingCallback(WasmCompileStreamingImpl);
  }
}
