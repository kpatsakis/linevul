    StateBase* writeDenseArray(uint32_t numProperties, uint32_t length, StateBase* state)
    {
        m_writer.writeDenseArray(numProperties, length);
        return pop(state);
    }
