  bool OnMatchedView(const v8::Local<v8::Value>& view_window) {
    views_->Set(v8::Integer::New(index_), view_window);
    index_++;

    if (view_type_ == ViewType::EXTENSION_BACKGROUND_PAGE)
      return false;  // There can be only one...

    return true;
  }
