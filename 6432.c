  void run() {
    if (!m_loader)
      return;
    ExecutionContext& context = m_loader->element()->document();
    InspectorInstrumentation::AsyncTask asyncTask(&context, this);
    if (m_scriptState->contextIsValid()) {
      ScriptState::Scope scope(m_scriptState.get());
      m_loader->doUpdateFromElement(m_shouldBypassMainWorldCSP,
                                    m_updateBehavior, m_requestURL,
                                    m_referrerPolicy);
    } else {
      m_loader->doUpdateFromElement(m_shouldBypassMainWorldCSP,
                                    m_updateBehavior, m_requestURL,
                                    m_referrerPolicy);
    }
  }
