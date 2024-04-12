V8Console::CommandLineAPIScope::CommandLineAPIScope(v8::Local<v8::Context> context, v8::Local<v8::Object> commandLineAPI, v8::Local<v8::Object> global)
    : m_context(context)
    , m_commandLineAPI(commandLineAPI)
    , m_global(global)
    , m_installedMethods(v8::Set::New(context->GetIsolate()))
    , m_cleanup(false)
{
    v8::Local<v8::Array> names;
    if (!m_commandLineAPI->GetOwnPropertyNames(context).ToLocal(&names))
        return;
    v8::Local<v8::External> externalThis = v8::External::New(context->GetIsolate(), this);
    for (size_t i = 0; i < names->Length(); ++i) {
        v8::Local<v8::Value> name;
        if (!names->Get(context, i).ToLocal(&name) || !name->IsName())
            continue;
        if (m_global->Has(context, name).FromMaybe(true))
            continue;
        if (!m_installedMethods->Add(context, name).ToLocal(&m_installedMethods))
            continue;
        if (!m_global->SetAccessor(context, v8::Local<v8::Name>::Cast(name), CommandLineAPIScope::accessorGetterCallback,
            CommandLineAPIScope::accessorSetterCallback, externalThis,
            v8::DEFAULT, v8::DontEnum).FromMaybe(false)) {
            bool removed = m_installedMethods->Delete(context, name).FromMaybe(false);
            DCHECK(removed);
            continue;
        }
    }
}
