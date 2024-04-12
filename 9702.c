    StateBase* writeSparseArray(uint32_t numProperties, uint32_t length, StateBase* state)
    {
        m_writer.writeSparseArray(numProperties, length);
        return pop(state);
    }
