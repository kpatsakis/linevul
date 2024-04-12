static void thread_check_init(void)
{
  g_main_thread = pthread_self();
}
