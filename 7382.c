static enum test_return test_binary_incr_impl(const char* key, uint8_t cmd) {
    union {
        protocol_binary_request_no_extras request;
        protocol_binary_response_no_extras response_header;
        protocol_binary_response_incr response;
        char bytes[1024];
    } send, receive;
    size_t len = arithmetic_command(send.bytes, sizeof(send.bytes), cmd,
                                    key, strlen(key), 1, 0, 0);

    int ii;
    for (ii = 0; ii < 10; ++ii) {
        safe_send(send.bytes, len, false);
        if (cmd == PROTOCOL_BINARY_CMD_INCREMENT) {
            safe_recv_packet(receive.bytes, sizeof(receive.bytes));
            validate_response_header(&receive.response_header, cmd,
                                     PROTOCOL_BINARY_RESPONSE_SUCCESS);
            assert(ntohll(receive.response.message.body.value) == ii);
        }
    }

    if (cmd == PROTOCOL_BINARY_CMD_INCREMENTQ) {
        test_binary_noop();
    }
    return TEST_PASS;
}
