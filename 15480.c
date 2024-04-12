  static v8::Handle<v8::Value> GetExtensionViews(const v8::Arguments& args) {
    if (args.Length() != 2)
      return v8::Undefined();

    if (!args[0]->IsInt32() || !args[1]->IsString())
      return v8::Undefined();

    int browser_window_id = args[0]->Int32Value();

    std::string view_type_string = *v8::String::Utf8Value(args[1]->ToString());
    StringToUpperASCII(&view_type_string);
    ViewType::Type view_type = ViewType::INVALID;
    if (view_type_string == ViewType::kBackgroundPage) {
      view_type = ViewType::EXTENSION_BACKGROUND_PAGE;
    } else if (view_type_string == ViewType::kInfobar) {
      view_type = ViewType::EXTENSION_INFOBAR;
    } else if (view_type_string == ViewType::kNotification) {
      view_type = ViewType::NOTIFICATION;
    } else if (view_type_string == ViewType::kTabContents) {
      view_type = ViewType::TAB_CONTENTS;
    } else if (view_type_string == ViewType::kPopup) {
      view_type = ViewType::EXTENSION_POPUP;
    } else if (view_type_string == ViewType::kExtensionDialog) {
      view_type = ViewType::EXTENSION_DIALOG;
    } else if (view_type_string != ViewType::kAll) {
      return v8::Undefined();
    }

    ExtensionImpl* v8_extension = GetFromArguments<ExtensionImpl>(args);
    const ::Extension* extension =
        v8_extension->GetExtensionForCurrentContext();
    if (!extension)
      return v8::Undefined();

    ExtensionViewAccumulator accumulator(extension->id(), browser_window_id,
                                         view_type);
    RenderView::ForEach(&accumulator);
    return accumulator.views();
  }
