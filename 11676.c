vmnc_handle_wmvj_rectangle (GstVMncDec * dec, struct RfbRectangle *rect,
    const guint8 * data, int len, gboolean decode)
{
  /* VM state info, not interesting for playback */
  if (len < 2) {
    GST_LOG_OBJECT (dec, "VM state data too short");
    return ERROR_INSUFFICIENT_DATA;
  }
  return 2;
}
