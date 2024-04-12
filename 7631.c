static enum test_return test_binary_appendq(void) {
    return test_binary_concat_impl("test_binary_appendq",
                                   PROTOCOL_BINARY_CMD_APPENDQ);
}
