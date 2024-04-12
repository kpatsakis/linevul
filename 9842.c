    void addResource(const char* url, const char* mime, PassRefPtr<SharedBuffer> data)
    {
        SerializedResource resource(toKURL(url), mime, data);
        m_resources.append(resource);
    }
