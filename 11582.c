http_SetResp(struct http *to, const char *proto, uint16_t status,
    const char *response)
{

	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	http_SetH(to, HTTP_HDR_PROTO, proto);
	assert(status >= 100 && status <= 999);
	to->status = status;
	http_SetH(to, HTTP_HDR_RESPONSE, response);
}
