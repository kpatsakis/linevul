int equalizer_enable(effect_context_t *context)
{
 equalizer_context_t *eq_ctxt = (equalizer_context_t *)context;

    ALOGV("%s", __func__);

 if (!offload_eq_get_enable_flag(&(eq_ctxt->offload_eq))) {
        offload_eq_set_enable_flag(&(eq_ctxt->offload_eq), true);
 if (eq_ctxt->ctl)
            offload_eq_send_params(eq_ctxt->ctl, &eq_ctxt->offload_eq,
                                   OFFLOAD_SEND_EQ_ENABLE_FLAG |
                                   OFFLOAD_SEND_EQ_BANDS_LEVEL);
 }
 return 0;
}
