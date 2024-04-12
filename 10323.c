e1000e_receive(E1000ECore *core, const uint8_t *buf, size_t size)
{
    const struct iovec iov = {
        .iov_base = (uint8_t *)buf,
        .iov_len = size
    };

    return e1000e_receive_iov(core, &iov, 1);
}
