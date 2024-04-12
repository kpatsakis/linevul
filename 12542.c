ksba_ocsp_get_status (ksba_ocsp_t ocsp, ksba_cert_t cert,
                      ksba_status_t *r_status,
                      ksba_isotime_t r_this_update,
                      ksba_isotime_t r_next_update,
                      ksba_isotime_t r_revocation_time,
                      ksba_crl_reason_t *r_reason)
{
  struct ocsp_reqitem_s *ri;

  if (!ocsp || !cert || !r_status)
    return gpg_error (GPG_ERR_INV_VALUE);
  if (!ocsp->requestlist)
    return gpg_error (GPG_ERR_MISSING_ACTION);

  /* Find the certificate.  We don't care about the issuer certificate
     and stop at the first match.  The implementation may be optimized
     by keeping track of the last certificate found to start with the
     next one then.  Given that a usual request consists only of a few
     certificates, this does not make much sense in reality. */
  for (ri=ocsp->requestlist; ri; ri = ri->next)
    if (ri->cert == cert)
      break;
  if (!ri)
    return gpg_error (GPG_ERR_NOT_FOUND);
  if (r_status)
    *r_status = ri->status;
  if (r_this_update)
    _ksba_copy_time (r_this_update, ri->this_update);
  if (r_next_update)
    _ksba_copy_time (r_next_update, ri->next_update);
  if (r_revocation_time)
    _ksba_copy_time (r_revocation_time, ri->revocation_time);
  if (r_reason)
    *r_reason = ri->revocation_reason;
  return 0;
}
