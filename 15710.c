    PassRefPtr<SharedBuffer> readFile(const char* fileName)
    {
        String filePath = m_filePath + fileName;
        return Platform::current()->unitTestSupport()->readFromFile(filePath);
    }
