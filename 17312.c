void auth_gssapi_display_status(
     char *msg,
     OM_uint32 major,
     OM_uint32 minor)
{
     auth_gssapi_display_status_1(msg, major, GSS_C_GSS_CODE, 0);
     auth_gssapi_display_status_1(msg, minor, GSS_C_MECH_CODE, 0);
}
