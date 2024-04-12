void Dispatcher::UpdateBindingsForContext(ScriptContext* context) {
  v8::HandleScope handle_scope(context->isolate());
  v8::Context::Scope context_scope(context->v8_context());

  switch (context->context_type()) {
    case Feature::UNSPECIFIED_CONTEXT:
    case Feature::WEB_PAGE_CONTEXT:
    case Feature::BLESSED_WEB_PAGE_CONTEXT:
      if (context->GetAvailability("app").is_available())
        RegisterBinding("app", context);
      if (context->GetAvailability("webstore").is_available())
        RegisterBinding("webstore", context);
      if (context->GetAvailability("dashboardPrivate").is_available())
        RegisterBinding("dashboardPrivate", context);
      if (IsRuntimeAvailableToContext(context))
        RegisterBinding("runtime", context);
      UpdateContentCapabilities(context);
      break;

    case Feature::BLESSED_EXTENSION_CONTEXT:
    case Feature::UNBLESSED_EXTENSION_CONTEXT:
    case Feature::CONTENT_SCRIPT_CONTEXT:
    case Feature::WEBUI_CONTEXT: {
      const FeatureProvider* api_feature_provider =
          FeatureProvider::GetAPIFeatures();
      for (const auto& map_entry : api_feature_provider->GetAllFeatures()) {
        if (map_entry.second->IsInternal())
          continue;

        if (api_feature_provider->GetParent(map_entry.second.get()) != nullptr)
          continue;

        if (map_entry.first == "test" &&
            !base::CommandLine::ForCurrentProcess()->HasSwitch(
                ::switches::kTestType)) {
          continue;
        }

        if (context->IsAnyFeatureAvailableToContext(*map_entry.second.get()))
          RegisterBinding(map_entry.first, context);
      }
      break;
    }
    case Feature::SERVICE_WORKER_CONTEXT:
      NOTREACHED();
      break;
  }
}
