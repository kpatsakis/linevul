frobnicate_signal_handler (DBusGProxy  *proxy,
			   int          val,
			   void        *user_data)
{
  n_times_frobnicate_received += 1;

  g_assert (val == 42);
  g_print ("Got Frobnicate signal\n");

  g_main_loop_quit (loop);
  g_source_remove (exit_timeout);
}
