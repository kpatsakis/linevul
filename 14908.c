v8::Persistent<v8::FunctionTemplate> V8Float64Array::GetTemplate()
{
    V8BindingPerIsolateData* data = V8BindingPerIsolateData::current();
    V8BindingPerIsolateData::TemplateMap::iterator result = data->templateMap().find(&info);
    if (result != data->templateMap().end())
        return result->second;

    v8::HandleScope handleScope;
    v8::Persistent<v8::FunctionTemplate> templ =
        ConfigureV8Float64ArrayTemplate(GetRawTemplate());
    data->templateMap().add(&info, templ);
    return templ;
}
