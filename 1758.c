IPV6DefragSturgesNovakLastTest(void)
{
    /* Expected data. */
    u_char expected[] = {
        "AAAAAAAA"
        "JJJJJJJJ"
        "JJJJJJJJ"
        "JJJJJJJJ"
        "JJJJJJJJ"
        "BBBBBBBB"
        "KKKKKKKK"
        "KKKKKKKK"
        "KKKKKKKK"
        "LLLLLLLL"
        "LLLLLLLL"
        "LLLLLLLL"
        "MMMMMMMM"
        "MMMMMMMM"
        "MMMMMMMM"
        "FFFFFFFF"
        "NNNNNNNN"
        "FFFFFFFF"
        "GGGGGGGG"
        "OOOOOOOO"
        "PPPPPPPP"
        "HHHHHHHH"
        "QQQQQQQQ"
        "QQQQQQQQ"
    };

    return IPV6DefragDoSturgesNovakTest(DEFRAG_POLICY_LAST, expected,
        sizeof(expected));
}
