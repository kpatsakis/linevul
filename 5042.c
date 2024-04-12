static void print_gss_error(OM_uint32 err_maj, OM_uint32 err_min)
{
  OM_uint32 maj_stat, min_stat;
  OM_uint32 msg_ctx = 0;
  gss_buffer_desc status_string;
  char buf_maj[512];
  char buf_min[512];

  do
  {
    maj_stat = gss_display_status(&min_stat, err_maj, GSS_C_GSS_CODE,
                                  GSS_C_NO_OID, &msg_ctx, &status_string);
    if (GSS_ERROR(maj_stat))
      break;
    size_t status_len = status_string.length;
    if (status_len >= sizeof(buf_maj))
      status_len = sizeof(buf_maj) - 1;
    strncpy(buf_maj, (char *) status_string.value, status_len);
    buf_maj[status_len] = '\0';
    gss_release_buffer(&min_stat, &status_string);

    maj_stat = gss_display_status(&min_stat, err_min, GSS_C_MECH_CODE,
                                  GSS_C_NULL_OID, &msg_ctx, &status_string);
    if (!GSS_ERROR(maj_stat))
    {
      status_len = status_string.length;
      if (status_len >= sizeof(buf_min))
        status_len = sizeof(buf_min) - 1;
      strncpy(buf_min, (char *) status_string.value, status_len);
      buf_min[status_len] = '\0';
      gss_release_buffer(&min_stat, &status_string);
    }
  } while (!GSS_ERROR(maj_stat) && msg_ctx != 0);

  mutt_debug(2, "((%s:%d )(%s:%d))\n", buf_maj, err_maj, buf_min, err_min);
}
