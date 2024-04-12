    void processInputAttribute(const NameType& attributeName, const String& attributeValue)
    {
        if (match(attributeName, srcAttr))
            setUrlToLoad(attributeValue, DisallowURLReplacement);
        else if (match(attributeName, typeAttr))
            m_inputIsImage = equalIgnoringCase(attributeValue, InputTypeNames::image);
    }
