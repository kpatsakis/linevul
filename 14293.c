static int session_init(struct session_s *session)
{
 size_t i;
 int status = 0;

    session->state = SESSION_STATE_INIT;
    session->id = 0;
    session->io = 0;
    session->created_msk = 0;
 for (i = 0; i < NUM_ID && status == 0; i++)
        status = effect_init(&session->effects[i], i);

 return status;
}
