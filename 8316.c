DumpMac(int dbg_level, const char* header_str, UCHAR* mac)
{
    DPrintf(dbg_level,("%s: %02x-%02x-%02x-%02x-%02x-%02x\n",
        header_str, mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]));

}
