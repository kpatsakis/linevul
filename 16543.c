    void fillHole()
    {
        COMPILE_ASSERT(sizeof(BufferValueType) == 2, BufferValueTypeIsTwoBytes);
        if (m_position % 2)
            *byteAt(m_position) = static_cast<uint8_t>(PaddingTag);
    }
