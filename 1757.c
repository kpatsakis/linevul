    bool contains(const v8::Handle<GCObject>& handle)
    {
        return m_map.contains(*handle);
    }
