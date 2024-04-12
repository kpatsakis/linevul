    StringCapturingFunction(ScriptState* scriptState, String* value)
        : ScriptFunction(scriptState)
        , m_value(value)
    {
    }
