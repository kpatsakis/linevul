WebWindowFeatures GetWindowFeaturesFromString(const String& feature_string) {
  WebWindowFeatures window_features;

  if (feature_string.IsEmpty())
    return window_features;

  window_features.menu_bar_visible = false;
  window_features.status_bar_visible = false;
  window_features.tool_bar_visible = false;
  window_features.scrollbars_visible = false;

  unsigned key_begin, key_end;
  unsigned value_begin, value_end;

  String buffer = feature_string.DeprecatedLower();
  unsigned length = buffer.length();
  for (unsigned i = 0; i < length;) {
    while (i < length && IsWindowFeaturesSeparator(buffer[i]))
      i++;
    key_begin = i;

    while (i < length && !IsWindowFeaturesSeparator(buffer[i]))
      i++;
    key_end = i;

    SECURITY_DCHECK(i <= length);

    while (i < length && buffer[i] != '=') {
      if (buffer[i] == ',' || !IsWindowFeaturesSeparator(buffer[i]))
        break;

      i++;
    }

    if (i < length && IsWindowFeaturesSeparator(buffer[i])) {
      while (i < length && IsWindowFeaturesSeparator(buffer[i])) {
        if (buffer[i] == ',')
          break;

        i++;
      }

      value_begin = i;

      SECURITY_DCHECK(i <= length);

      while (i < length && !IsWindowFeaturesSeparator(buffer[i]))
        i++;

      value_end = i;

      SECURITY_DCHECK(i <= length);
    } else {
      value_begin = i;
      value_end = i;
    }

    String key_string(
        buffer.Substring(key_begin, key_end - key_begin).LowerASCII());
    String value_string(
        buffer.Substring(value_begin, value_end - value_begin).LowerASCII());

    int value;
    if (value_string.IsEmpty() || value_string == "yes")
      value = 1;
    else
      value = value_string.ToInt();

    if (key_string.IsEmpty())
      continue;

    if (key_string == "left" || key_string == "screenx") {
      window_features.x_set = true;
      window_features.x = value;
    } else if (key_string == "top" || key_string == "screeny") {
      window_features.y_set = true;
      window_features.y = value;
    } else if (key_string == "width" || key_string == "innerwidth") {
      window_features.width_set = true;
      window_features.width = value;
    } else if (key_string == "height" || key_string == "innerheight") {
      window_features.height_set = true;
      window_features.height = value;
    } else if (key_string == "menubar") {
      window_features.menu_bar_visible = value;
    } else if (key_string == "toolbar" || key_string == "location") {
      window_features.tool_bar_visible |= static_cast<bool>(value);
    } else if (key_string == "status") {
      window_features.status_bar_visible = value;
    } else if (key_string == "scrollbars") {
      window_features.scrollbars_visible = value;
    } else if (key_string == "resizable") {
      window_features.resizable = value;
    } else if (key_string == "noopener") {
      window_features.noopener = true;
    } else if (key_string == "background") {
      window_features.background = true;
    } else if (key_string == "persistent") {
      window_features.persistent = true;
    }
  }

  return window_features;
}
