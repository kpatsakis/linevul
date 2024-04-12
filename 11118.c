static gboolean rpc_event_dispatch(GSource *source, GSourceFunc callback, gpointer connection)
{
  return rpc_dispatch(connection) != RPC_ERROR_CONNECTION_CLOSED;
}
