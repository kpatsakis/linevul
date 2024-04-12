parse_response_status (ksba_ocsp_t ocsp,
                       unsigned char const **data, size_t *datalen,
                       size_t *rlength)
{
  gpg_error_t err;
  struct tag_info ti;
  char *oid;

  *rlength = 0;
  /* Parse the OCSPResponse sequence. */
  err = parse_sequence (data, datalen, &ti);
  if (err)
    return err;
  /* Parse the OCSPResponseStatus. */
  err = parse_enumerated (data, datalen, &ti, 1);
  if (err)
    return err;
  switch (**data)
    {
    case 0:  ocsp->response_status = KSBA_OCSP_RSPSTATUS_SUCCESS; break;
    case 1:  ocsp->response_status = KSBA_OCSP_RSPSTATUS_MALFORMED; break;
    case 2:  ocsp->response_status = KSBA_OCSP_RSPSTATUS_INTERNAL; break;
    case 3:  ocsp->response_status = KSBA_OCSP_RSPSTATUS_TRYLATER; break;
    case 5:  ocsp->response_status = KSBA_OCSP_RSPSTATUS_SIGREQUIRED; break;
    case 6:  ocsp->response_status = KSBA_OCSP_RSPSTATUS_UNAUTHORIZED; break;
    default: ocsp->response_status = KSBA_OCSP_RSPSTATUS_OTHER; break;
    }
  parse_skip (data, datalen, &ti);

  if (ocsp->response_status)
      return 0; /* This is an error reponse; we have to stop here. */

  /* We have a successful reponse status, thus we check that
     ResponseBytes are actually available. */
  err = parse_context_tag (data, datalen, &ti, 0);
  if (err)
    return err;
  err = parse_sequence (data, datalen, &ti);
  if (err)
    return err;
  err = parse_object_id_into_str (data, datalen, &oid);
  if (err)
    return err;
  if (strcmp (oid, oidstr_ocsp_basic))
    {
      xfree (oid);
      return gpg_error (GPG_ERR_UNSUPPORTED_PROTOCOL);
    }
  xfree (oid);

  /* Check that the next field is an octet string. */
  err = parse_octet_string (data, datalen, &ti);
  if (err)
    return err;
  *rlength = ti.length;
  return 0;
}
