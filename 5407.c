static const effect_descriptor_t *get_descriptor(const effect_uuid_t *uuid)
{
 size_t i;
 for (i = 0; i < NUM_ID; i++)
 if (memcmp(&descriptors[i]->uuid, uuid, sizeof(effect_uuid_t)) == 0)
 return descriptors[i];

 return NULL;
}
