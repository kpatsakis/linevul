static void NPN_InvalidateRect(NPP npp, NPRect* invalidRect)
{
    RefPtr<NetscapePlugin> plugin = NetscapePlugin::fromNPP(npp);
    plugin->invalidate(invalidRect);
}
