iter_set_sequence (DBusMessageDataIter *iter,
                   int                  sequence)
{
  _dbus_assert (sequence >= 0);
  iter->sequence_nos[iter->depth] = sequence;
}
