gss_sign (minor_status,
          context_handle,
          qop_req,
          message_buffer,
          msg_token)

OM_uint32 *		minor_status;
gss_ctx_id_t		context_handle;
int			qop_req;
gss_buffer_t		message_buffer;
gss_buffer_t		msg_token;

{
	return (gss_get_mic(minor_status, context_handle, (gss_qop_t) qop_req,
			    message_buffer, msg_token));
}
