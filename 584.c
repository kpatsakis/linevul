local void outb_check(void *dummy)
{
    size_t len;

    (void)dummy;

    Trace(("-- launched decompress check thread"));
    do {
        possess(outb_check_more);
        wait_for(outb_check_more, TO_BE, 1);
        len = out_len;
        g.out_check = CHECK(g.out_check, out_copy, len);
        Trace(("-- decompress checked %lu bytes", len));
        twist(outb_check_more, TO, 0);
    } while (len);
    Trace(("-- exited decompress check thread"));
}
