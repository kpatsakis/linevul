void Document::processReferrerPolicy(const String& policy)
{
    ASSERT(!policy.isNull());

    m_referrerPolicy = ReferrerPolicyDefault;

    if (equalIgnoringCase(policy, "never"))
        m_referrerPolicy = ReferrerPolicyNever;
    else if (equalIgnoringCase(policy, "always"))
        m_referrerPolicy = ReferrerPolicyAlways;
    else if (equalIgnoringCase(policy, "origin"))
        m_referrerPolicy = ReferrerPolicyOrigin;
}
