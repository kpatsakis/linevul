void ContentSecurityPolicy::applyPolicySideEffectsToExecutionContext() {
  DCHECK(m_executionContext &&
         m_executionContext->securityContext().getSecurityOrigin());

  setupSelf(*m_executionContext->securityContext().getSecurityOrigin());

  if (Document* document = this->document()) {
    if (m_sandboxMask != SandboxNone) {
      UseCounter::count(document, UseCounter::SandboxViaCSP);
      document->enforceSandboxFlags(m_sandboxMask);
    }
    if (m_treatAsPublicAddress)
      document->setAddressSpace(WebAddressSpacePublic);

    document->enforceInsecureRequestPolicy(m_insecureRequestPolicy);
    if (m_insecureRequestPolicy & kUpgradeInsecureRequests) {
      UseCounter::count(document, UseCounter::UpgradeInsecureRequestsEnabled);
      if (!document->url().host().isEmpty())
        document->addInsecureNavigationUpgrade(
            document->url().host().impl()->hash());
    }

    for (const auto& consoleMessage : m_consoleMessages)
      m_executionContext->addConsoleMessage(consoleMessage);
    m_consoleMessages.clear();

    for (const auto& policy : m_policies) {
      UseCounter::count(*document, getUseCounterType(policy->headerType()));
      if (policy->allowDynamic())
        UseCounter::count(*document, UseCounter::CSPWithStrictDynamic);
    }
  }

  if (!m_disableEvalErrorMessage.isNull())
    m_executionContext->disableEval(m_disableEvalErrorMessage);
}
