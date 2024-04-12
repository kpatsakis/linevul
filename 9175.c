static void validate_response_header(protocol_binary_response_no_extras *response,
                                     uint8_t cmd, uint16_t status)
{
    assert(response->message.header.response.magic == PROTOCOL_BINARY_RES);
    assert(response->message.header.response.opcode == cmd);
    assert(response->message.header.response.datatype == PROTOCOL_BINARY_RAW_BYTES);
    assert(response->message.header.response.status == status);
    assert(response->message.header.response.opaque == 0xdeadbeef);

    if (status == PROTOCOL_BINARY_RESPONSE_SUCCESS) {
        switch (cmd) {
        case PROTOCOL_BINARY_CMD_ADDQ:
        case PROTOCOL_BINARY_CMD_APPENDQ:
        case PROTOCOL_BINARY_CMD_DECREMENTQ:
        case PROTOCOL_BINARY_CMD_DELETEQ:
        case PROTOCOL_BINARY_CMD_FLUSHQ:
        case PROTOCOL_BINARY_CMD_INCREMENTQ:
        case PROTOCOL_BINARY_CMD_PREPENDQ:
        case PROTOCOL_BINARY_CMD_QUITQ:
        case PROTOCOL_BINARY_CMD_REPLACEQ:
        case PROTOCOL_BINARY_CMD_SETQ:
            assert("Quiet command shouldn't return on success" == NULL);
        default:
            break;
        }

        switch (cmd) {
        case PROTOCOL_BINARY_CMD_ADD:
        case PROTOCOL_BINARY_CMD_REPLACE:
        case PROTOCOL_BINARY_CMD_SET:
        case PROTOCOL_BINARY_CMD_APPEND:
        case PROTOCOL_BINARY_CMD_PREPEND:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen == 0);
            assert(response->message.header.response.cas != 0);
            break;
        case PROTOCOL_BINARY_CMD_FLUSH:
        case PROTOCOL_BINARY_CMD_NOOP:
        case PROTOCOL_BINARY_CMD_QUIT:
        case PROTOCOL_BINARY_CMD_DELETE:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen == 0);
            assert(response->message.header.response.cas == 0);
            break;

        case PROTOCOL_BINARY_CMD_DECREMENT:
        case PROTOCOL_BINARY_CMD_INCREMENT:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen == 8);
            assert(response->message.header.response.cas != 0);
            break;

        case PROTOCOL_BINARY_CMD_STAT:
            assert(response->message.header.response.extlen == 0);
            /* key and value exists in all packets except in the terminating */
            assert(response->message.header.response.cas == 0);
            break;

        case PROTOCOL_BINARY_CMD_VERSION:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 0);
            assert(response->message.header.response.bodylen != 0);
            assert(response->message.header.response.cas == 0);
            break;

        case PROTOCOL_BINARY_CMD_GET:
        case PROTOCOL_BINARY_CMD_GETQ:
            assert(response->message.header.response.keylen == 0);
            assert(response->message.header.response.extlen == 4);
            assert(response->message.header.response.cas != 0);
            break;

        case PROTOCOL_BINARY_CMD_GETK:
        case PROTOCOL_BINARY_CMD_GETKQ:
            assert(response->message.header.response.keylen != 0);
            assert(response->message.header.response.extlen == 4);
            assert(response->message.header.response.cas != 0);
            break;

        default:
            /* Undefined command code */
            break;
        }
    } else {
        assert(response->message.header.response.cas == 0);
        assert(response->message.header.response.extlen == 0);
        if (cmd != PROTOCOL_BINARY_CMD_GETK) {
            assert(response->message.header.response.keylen == 0);
        }
    }
}
