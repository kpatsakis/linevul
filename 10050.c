    void writeUint32(uint32_t value)
    {
        append(Uint32Tag);
        doWriteUint32(value);
    }
