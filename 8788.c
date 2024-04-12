static size_t ZSTD_noCompressBlock (void* dst, size_t dstCapacity, const void* src, size_t srcSize, U32 lastBlock)
{
    U32 const cBlockHeader24 = lastBlock + (((U32)bt_raw)<<1) + (U32)(srcSize << 3);
    if (srcSize + ZSTD_blockHeaderSize > dstCapacity) return ERROR(dstSize_tooSmall);
    MEM_writeLE24(dst, cBlockHeader24);
    memcpy((BYTE*)dst + ZSTD_blockHeaderSize, src, srcSize);
    return ZSTD_blockHeaderSize + srcSize;
}
