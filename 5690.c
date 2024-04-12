int effect_get_descriptor(effect_handle_t   self,
 effect_descriptor_t *descriptor)
{
 effect_context_t *context = (effect_context_t *)self;

 if (!effect_exists(context) || (descriptor == NULL))
 return -EINVAL;

 *descriptor = *context->desc;

 return 0;
}
