bool xmp_files_can_put_xmp_cstr(XmpFilePtr xf, const char* xmp_packet, size_t len)
{
  CHECK_PTR(xf, false);
  RESET_ERROR;
  SXMPFiles *txf = reinterpret_cast<SXMPFiles*>(xf);
  bool result = false;

  try {
    result = txf->CanPutXMP(xmp_packet, len);
  }
  catch(const XMP_Error & e) {
    set_error(e);
    return false;
  }
  return result;
}
