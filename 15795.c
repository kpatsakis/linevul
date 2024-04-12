int PreProcessingFx_GetDescriptor(effect_handle_t   self,
 effect_descriptor_t *pDescriptor)
{
 preproc_effect_t * effect = (preproc_effect_t *) self;

 if (effect == NULL || pDescriptor == NULL) {
 return -EINVAL;
 }

 *pDescriptor = *sDescriptors[effect->procId];

 return 0;
}
