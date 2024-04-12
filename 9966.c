local int get_header(int save)
{
    unsigned magic;             /* magic header */
    int method;                 /* compression method */
    int flags;                  /* header flags */
    unsigned fname, extra;      /* name and extra field lengths */
    unsigned tmp2;              /* for macro */
    unsigned long tmp4;         /* for macro */

    /* clear return information */
    if (save) {
        g.stamp = 0;
        RELEASE(g.hname);
    }

    /* see if it's a gzip, zlib, or lzw file */
    g.form = -1;
    g.magic1 = GET();
    if (g.in_eof)
        return -1;
    magic = g.magic1 << 8;
    magic += GET();
    if (g.in_eof)
        return -2;
    if (magic % 31 == 0) {          /* it's zlib */
        g.form = 1;
        return (int)((magic >> 8) & 0xf);
    }
    if (magic == 0x1f9d)            /* it's lzw */
        return 257;
    if (magic == 0x504b) {          /* it's zip */
        magic = GET2();             /* the rest of the signature */
        if (g.in_eof)
            return -3;
        if (magic == 0x0201 || magic == 0x0806)
            return -5;              /* central header or archive extra */
        if (magic != 0x0403)
            return -4;              /* not a local header */
        SKIP(2);
        flags = GET2();
        if (g.in_eof)
            return -3;
        if (flags & 0xfff0)
            return -4;
        method = GET();             /* return low byte of method or 256 */
        if (GET() != 0 || flags & 1)
            method = 256;           /* unknown or encrypted */
        if (g.in_eof)
            return -3;
        if (save)
            g.stamp = dos2time(GET4());
        else
            SKIP(4);
        g.zip_crc = GET4();
        g.zip_clen = GET4();
        g.zip_ulen = GET4();
        fname = GET2();
        extra = GET2();
        if (save) {
            char *next = g.hname = MALLOC(fname + 1);
            if (g.hname == NULL)
                bail("not enough memory", "");
            while (fname > g.in_left) {
                memcpy(next, g.in_next, g.in_left);
                fname -= g.in_left;
                next += g.in_left;
                if (load() == 0)
                    return -3;
            }
            memcpy(next, g.in_next, fname);
            g.in_left -= fname;
            g.in_next += fname;
            next += fname;
            *next = 0;
        }
        else
            SKIP(fname);
        read_extra(extra, save);
        g.form = 2 + ((flags & 8) >> 3);
        return g.in_eof ? -3 : method;
    }
    if (magic != 0x1f8b) {          /* not gzip */
        g.in_left++;    /* unget second magic byte */
        g.in_next--;
        return -2;
    }

    /* it's gzip -- get method and flags */
    method = GET();
    flags = GET();
    if (g.in_eof)
        return -1;
    if (flags & 0xe0)
        return -4;

    /* get time stamp */
    if (save)
        g.stamp = tolong(GET4());
    else
        SKIP(4);

    /* skip extra field and OS */
    SKIP(2);

    /* skip extra field, if present */
    if (flags & 4) {
        extra = GET2();
        if (g.in_eof)
            return -3;
        SKIP(extra);
    }

    /* read file name, if present, into allocated memory */
    if ((flags & 8) && save) {
        unsigned char *end;
        size_t copy, have, size = 128;
        g.hname = MALLOC(size);
        if (g.hname == NULL)
            bail("not enough memory", "");
        have = 0;
        do {
            if (g.in_left == 0 && load() == 0)
                return -3;
            end = memchr(g.in_next, 0, g.in_left);
            copy = end == NULL ? g.in_left : (size_t)(end - g.in_next) + 1;
            if (have + copy > size) {
                while (have + copy > (size <<= 1))
                    ;
                g.hname = REALLOC(g.hname, size);
                if (g.hname == NULL)
                    bail("not enough memory", "");
            }
            memcpy(g.hname + have, g.in_next, copy);
            have += copy;
            g.in_left -= copy;
            g.in_next += copy;
        } while (end == NULL);
    }
    else if (flags & 8)
        while (GET() != 0)
            if (g.in_eof)
                return -3;

    /* skip comment */
    if (flags & 16)
        while (GET() != 0)
            if (g.in_eof)
                return -3;

    /* skip header crc */
    if (flags & 2)
        SKIP(2);

    /* return gzip compression method */
    g.form = 0;
    return method;
}
