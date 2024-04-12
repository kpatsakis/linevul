static int vol_effect_get_descriptor(effect_handle_t   self,
 effect_descriptor_t *descriptor)
{
 vol_listener_context_t *context = (vol_listener_context_t *)self;
    ALOGV("%s Called ", __func__);

 if (descriptor == NULL) {
        ALOGE("%s: descriptor is NULL", __func__);
 return -EINVAL;
 }

 *descriptor = *context->desc;
 return 0;
}
