static enum test_return test_binary_replaceq(void) {
    return test_binary_replace_impl("test_binary_replaceq",
                                    PROTOCOL_BINARY_CMD_REPLACEQ);
}
