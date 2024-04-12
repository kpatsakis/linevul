void WebPluginDelegatePepper::didChooseFile(
    const WebKit::WebVector<WebKit::WebString>& file_names) {
  if (file_names.isEmpty()) {
    current_choose_file_callback_(NULL, 0, current_choose_file_user_data_);
  } else {
    std::vector<std::string> file_strings;
    file_strings.resize(file_names.size());
    for (size_t i = 0; i < file_names.size(); i++)
      file_strings[i] = file_names[0].utf8();

    std::vector<const char*> pointers_to_strings;
    pointers_to_strings.resize(file_strings.size());
    for (size_t i = 0; i < file_strings.size(); i++)
      pointers_to_strings[i] = file_strings[i].c_str();

    current_choose_file_callback_(
        &pointers_to_strings[0],
        static_cast<int>(pointers_to_strings.size()),
        current_choose_file_user_data_);
  }
}
