vcard_init_buffer_response(VCard *card, unsigned char *buf, int len)
{
    VCardResponse *response;
    VCardBufferResponse *buffer_response;

    buffer_response = vcard_get_buffer_response(card);
    if (buffer_response) {
        vcard_set_buffer_response(card, NULL);
        vcard_buffer_response_delete(buffer_response);
    }
    buffer_response = vcard_buffer_response_new(buf, len);
    if (buffer_response == NULL) {
        return NULL;
    }
    response = vcard_response_new_status_bytes(VCARD7816_SW1_RESPONSE_BYTES,
                                               len > 255 ? 0 : len);
    if (response == NULL) {
        return NULL;
    }
    vcard_set_buffer_response(card, buffer_response);
    return response;
}
