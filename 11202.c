const KURL& Document::baseURLForOverride(const KURL& baseURLOverride) const
{
    const KURL* baseURLFromParent = 0;
    bool shouldUseParentBaseURL = baseURLOverride.isEmpty();
    if (!shouldUseParentBaseURL) {
        const KURL& aboutBlankURL = blankURL();
        shouldUseParentBaseURL = (baseURLOverride == aboutBlankURL);
    }
    if (shouldUseParentBaseURL) {
        if (Document* parent = parentDocument())
            baseURLFromParent = &parent->baseURL();
    }
    return baseURLFromParent ? *baseURLFromParent : baseURLOverride;
}
