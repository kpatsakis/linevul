void SSL3_RECORD_set_seq_num(SSL3_RECORD *r, const unsigned char *seq_num)
{
    memcpy(r->seq_num, seq_num, SEQ_NUM_SIZE);
}
