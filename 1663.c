bool GetStringProperty(
    XID window, const std::string& property_name, std::string* value) {
  Atom type = None;
  int format = 0;  // size in bits of each item in 'property'
  unsigned long num_items = 0;
  unsigned char* property = NULL;

  int result = GetProperty(window, property_name, 1024,
                           &type, &format, &num_items, &property);
  if (result != Success)
    return false;

  if (format != 8) {
    XFree(property);
    return false;
  }

  value->assign(reinterpret_cast<char*>(property), num_items);
  XFree(property);
  return true;
}
