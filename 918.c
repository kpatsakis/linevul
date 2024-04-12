static int set_adapter_property(const bt_property_t *property)
{
 /* sanity check */
 if (interface_ready() == FALSE)
 return BT_STATUS_NOT_READY;

 return btif_set_adapter_property(property);
}
