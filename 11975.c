read_key (struct key *key, const struct key_type *kt, struct buffer *buf)
{
  uint8_t cipher_length;
  uint8_t hmac_length;

  CLEAR (*key);
  if (!buf_read (buf, &cipher_length, 1))
    goto read_err;
  if (!buf_read (buf, &hmac_length, 1))
    goto read_err;

  if (!buf_read (buf, key->cipher, cipher_length))
    goto read_err;
  if (!buf_read (buf, key->hmac, hmac_length))
    goto read_err;

  if (cipher_length != kt->cipher_length || hmac_length != kt->hmac_length)
    goto key_len_err;

  return 1;

read_err:
  msg (D_TLS_ERRORS, "TLS Error: error reading key from remote");
  return -1;

key_len_err:
  msg (D_TLS_ERRORS,
       "TLS Error: key length mismatch, local cipher/hmac %d/%d, remote cipher/hmac %d/%d",
       kt->cipher_length, kt->hmac_length, cipher_length, hmac_length);
  return 0;
}
