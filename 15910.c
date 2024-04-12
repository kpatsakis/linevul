htmlcdataDebug(void *ctx ATTRIBUTE_UNUSED, const xmlChar *ch, int len)
{
    unsigned char output[40];
    int inlen = len, outlen = 30;

    htmlEncodeEntities(output, &outlen, ch, &inlen, 0);
    output[outlen] = 0;

    fprintf(SAXdebug, "SAX.cdata(%s, %d)\n", output, len);
}
