static void init_poll(int h)
{
 int i;
    ts[h].poll_count = 0;
    ts[h].thread_id = -1;
    ts[h].callback = NULL;
    ts[h].cmd_callback = NULL;
 for(i = 0; i < MAX_POLL; i++)
 {
        ts[h].ps[i].pfd.fd = -1;
        ts[h].psi[i] = -1;
 }
    init_cmd_fd(h);
}
