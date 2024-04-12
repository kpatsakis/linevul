bool PropertyHasChildren(IBusProperty* prop) {
  return prop && prop->sub_props && ibus_prop_list_get(prop->sub_props, 0);
}
