bus_activation_ref (BusActivation *activation)
{
  _dbus_assert (activation->refcount > 0);

  activation->refcount += 1;

  return activation;
}
