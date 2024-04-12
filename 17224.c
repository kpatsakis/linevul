void CSPSourceList::parse(const UChar* begin, const UChar* end)
{
    if (isSourceListNone(begin, end))
        return;

    const UChar* position = begin;
    while (position < end) {
        skipWhile<UChar, isASCIISpace>(position, end);
        if (position == end)
            return;

        const UChar* beginSource = position;
        skipWhile<UChar, isSourceCharacter>(position, end);

        String scheme, host, path;
        int port = 0;
        CSPSource::WildcardDisposition hostWildcard = CSPSource::NoWildcard;
        CSPSource::WildcardDisposition portWildcard = CSPSource::NoWildcard;

        if (parseSource(beginSource, position, scheme, host, port, path, hostWildcard, portWildcard)) {
            if (scheme.isEmpty() && host.isEmpty())
                continue;
            if (m_policy->isDirectiveName(host))
                m_policy->reportDirectiveAsSourceExpression(m_directiveName, host);
            m_list.append(CSPSource(m_policy, scheme, host, port, path, hostWildcard, portWildcard));
        } else {
            m_policy->reportInvalidSourceExpression(m_directiveName, String(beginSource, position - beginSource));
        }

        ASSERT(position == end || isASCIISpace(*position));
    }
}
