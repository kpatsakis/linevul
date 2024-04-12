ProfileNameIdleTimeMap* ScriptProfiler::currentProfileNameIdleTimeMap()
{
    AtomicallyInitializedStatic(WTF::ThreadSpecific<ProfileNameIdleTimeMap>*, map = new WTF::ThreadSpecific<ProfileNameIdleTimeMap>);
    return *map;
}
