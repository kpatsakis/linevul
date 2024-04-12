cib_remote_inputfd(cib_t * cib)
{
    cib_remote_opaque_t *private = cib->variant_opaque;

    return private->callback.socket;
}
