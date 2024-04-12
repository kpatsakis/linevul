ZSTD_CDict* ZSTD_createCDict_advanced(const void* dictBuffer, size_t dictSize,
                                      ZSTD_dictLoadMethod_e dictLoadMethod,
                                      ZSTD_dictContentType_e dictContentType,
                                      ZSTD_compressionParameters cParams, ZSTD_customMem customMem)
{
    DEBUGLOG(3, "ZSTD_createCDict_advanced, mode %u", (U32)dictContentType);
    if (!customMem.customAlloc ^ !customMem.customFree) return NULL;

    {   ZSTD_CDict* const cdict = (ZSTD_CDict*)ZSTD_malloc(sizeof(ZSTD_CDict), customMem);
        size_t const workspaceSize = HUF_WORKSPACE_SIZE + ZSTD_sizeof_matchState(&cParams, /* forCCtx */ 0);
        void* const workspace = ZSTD_malloc(workspaceSize, customMem);

        if (!cdict || !workspace) {
            ZSTD_free(cdict, customMem);
            ZSTD_free(workspace, customMem);
            return NULL;
        }
        cdict->customMem = customMem;
        cdict->workspace = workspace;
        cdict->workspaceSize = workspaceSize;
        if (ZSTD_isError( ZSTD_initCDict_internal(cdict,
                                        dictBuffer, dictSize,
                                        dictLoadMethod, dictContentType,
                                        cParams) )) {
            ZSTD_freeCDict(cdict);
            return NULL;
        }

        return cdict;
    }
}
