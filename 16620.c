TmEcode StreamTcpThreadDeinit(ThreadVars *tv, void *data)
{
    SCEnter();
    StreamTcpThread *stt = (StreamTcpThread *)data;
    if (stt == NULL) {
        return TM_ECODE_OK;
    }

    /* XXX */

    /* free reassembly ctx */
    StreamTcpReassembleFreeThreadCtx(stt->ra_ctx);

    /* clear memory */
    memset(stt, 0, sizeof(StreamTcpThread));

    SCFree(stt);
    SCReturnInt(TM_ECODE_OK);
}
