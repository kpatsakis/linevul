parse_SET_IP_TTL(char *arg, struct ofpbuf *ofpacts,
                  enum ofputil_protocol *usable_protocols OVS_UNUSED)
{
    uint8_t ttl;
    char *error;

    error = str_to_u8(arg, "TTL", &ttl);
    if (error) {
        return error;
    }

    ofpact_put_SET_IP_TTL(ofpacts)->ttl = ttl;
    return NULL;
}
