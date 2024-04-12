static void delayed_calls_add(int type, gpointer data)
{
  DelayedCall *dcall = NPW_MemNew(DelayedCall, 1);
  if (dcall == NULL)
	return;
  dcall->type = type;
  dcall->data = data;
  g_delayed_calls = g_list_append(g_delayed_calls, dcall);

  if (g_delayed_calls_id == 0)
	g_delayed_calls_id = g_idle_add_full(G_PRIORITY_LOW,
										 delayed_calls_process_cb, NULL, NULL);
}
