void V8Proxy::registerExtension(v8::Extension* extension)
{
    registerExtensionWithV8(extension);
    staticExtensionsList().append(extension);
}
