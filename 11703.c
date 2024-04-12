static int fx_process(effect_handle_t     self,
 audio_buffer_t *inBuffer,
 audio_buffer_t *outBuffer)
{
 struct effect_s *effect = (struct effect_s *)self;
 struct session_s *session;

 if (effect == NULL) {
        ALOGV("fx_process() ERROR effect == NULL");
 return -EINVAL;
 }

 if (inBuffer == NULL  || inBuffer->raw == NULL  ||
            outBuffer == NULL || outBuffer->raw == NULL) {
        ALOGW("fx_process() ERROR bad pointer");
 return -EINVAL;
 }

    session = (struct session_s *)effect->session;

    session->processed_msk |= (1<<effect->id);

 if ((session->processed_msk & session->enabled_msk) == session->enabled_msk) {
        effect->session->processed_msk = 0;
 return 0;
 } else
 return -ENODATA;
}
