void WriteVirtIODeviceWord(ULONG_PTR ulRegister, u16 wValue)
{
#if 1
    NdisRawWritePortUshort(ulRegister, wValue);
#else
    static int nCounterToFail = 0;
    static const int StartFail = 200, StopFail = 600;
    BOOLEAN bFail = FALSE;
    DPrintf(6, ("%s> R[%x] = %x\n", __FUNCTION__, (ULONG)ulRegister, wValue) );
    if ((ulRegister & 0x1F) == 0x10)
    {
        nCounterToFail++;
        bFail = nCounterToFail >= StartFail && nCounterToFail < StopFail;
    }
    if (!bFail) NdisRawWritePortUshort(ulRegister, wValue);
    else
    {
        DPrintf(0, ("%s> FAILING R[%x] = %x\n", __FUNCTION__, (ULONG)ulRegister, wValue) );
    }
#endif
}
