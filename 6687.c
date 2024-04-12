ksba_ocsp_build_request (ksba_ocsp_t ocsp,
                         unsigned char **r_buffer, size_t *r_buflen)
{
  gpg_error_t err;

  if (!ocsp || !r_buffer || !r_buflen)
    return gpg_error (GPG_ERR_INV_VALUE);
  *r_buffer = NULL;
  *r_buflen = 0;

  if (!ocsp->requestlist)
    return gpg_error (GPG_ERR_MISSING_ACTION);
  if (!ocsp->request_buffer)
    {
      /* No prepare done, do it now. */
      err = ksba_ocsp_prepare_request (ocsp);
      if (err)
        return err;
      assert (ocsp->request_buffer);
    }
  *r_buffer = ocsp->request_buffer;
  *r_buflen = ocsp->request_buflen;
  ocsp->request_buffer = NULL;
  ocsp->request_buflen = 0;
  return 0;
}
