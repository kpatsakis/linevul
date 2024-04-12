local void write_thread(void *dummy)
{
    long seq;                       /* next sequence number looking for */
    struct job *job;                /* job pulled and working on */
    size_t len;                     /* input length */
    int more;                       /* true if more chunks to write */
    unsigned long head;             /* header length */
    unsigned long ulen;             /* total uncompressed size (overflow ok) */
    unsigned long clen;             /* total compressed size (overflow ok) */
    unsigned long check;            /* check value of uncompressed data */

    (void)dummy;

    /* build and write header */
    Trace(("-- write thread running"));
    head = put_header();

    /* process output of compress threads until end of input */
    ulen = clen = 0;
    check = CHECK(0L, Z_NULL, 0);
    seq = 0;
    do {
        /* get next write job in order */
        possess(write_first);
        wait_for(write_first, TO_BE, seq);
        job = write_head;
        write_head = job->next;
        twist(write_first, TO, write_head == NULL ? -1 : write_head->seq);

        /* update lengths, save uncompressed length for COMB */
        more = job->more;
        len = job->in->len;
        drop_space(job->in);
        ulen += (unsigned long)len;
        clen += (unsigned long)(job->out->len);

        /* write the compressed data and drop the output buffer */
        Trace(("-- writing #%ld", seq));
        writen(g.outd, job->out->buf, job->out->len);
        drop_space(job->out);
        Trace(("-- wrote #%ld%s", seq, more ? "" : " (last)"));

        /* wait for check calculation to complete, then combine, once
           the compress thread is done with the input, release it */
        possess(job->calc);
        wait_for(job->calc, TO_BE, 1);
        release(job->calc);
        check = COMB(check, job->check, len);

        /* free the job */
        free_lock(job->calc);
        FREE(job);

        /* get the next buffer in sequence */
        seq++;
    } while (more);

    /* write trailer */
    put_trailer(ulen, clen, check, head);

    /* verify no more jobs, prepare for next use */
    possess(compress_have);
    assert(compress_head == NULL && peek_lock(compress_have) == 0);
    release(compress_have);
    possess(write_first);
    assert(write_head == NULL);
    twist(write_first, TO, -1);
}
