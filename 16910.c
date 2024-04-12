    StateBase* handleError(Status errorStatus, const String& message, StateBase* state)
    {
        ASSERT(errorStatus != Success);
        m_status = errorStatus;
        m_errorMessage = message;
        while (state) {
            StateBase* tmp = state->nextState();
            delete state;
            state = tmp;
        }
        return new ErrorState;
    }
