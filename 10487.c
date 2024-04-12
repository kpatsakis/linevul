void DTLS_RECORD_LAYER_resync_write(RECORD_LAYER *rl)
{
    memcpy(rl->write_sequence, rl->read_sequence, sizeof(rl->write_sequence));
}
