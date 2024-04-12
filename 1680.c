void WriteOutput(FILE *fid, u8 *data, u32 picSize)
{
 if (fid)
        fwrite(data, 1, picSize, fid);
}
