void PageSerializer::serializeCSSStyleSheet(CSSStyleSheet* styleSheet, const KURL& url)
{
    StringBuilder cssText;
    for (unsigned i = 0; i < styleSheet->length(); ++i) {
        CSSRule* rule = styleSheet->item(i);
        String itemText = rule->cssText();
        if (!itemText.isEmpty()) {
            cssText.append(itemText);
            if (i < styleSheet->length() - 1)
                cssText.append("\n\n");
        }
        Document* document = styleSheet->ownerDocument();
        if (rule->type() == CSSRule::IMPORT_RULE) {
            CSSImportRule* importRule = toCSSImportRule(rule);
            KURL importURL = document->completeURL(importRule->href());
            if (m_resourceURLs.contains(importURL))
                continue;
            serializeCSSStyleSheet(importRule->styleSheet(), importURL);
        } else if (rule->type() == CSSRule::FONT_FACE_RULE) {
            retrieveResourcesForProperties(toCSSFontFaceRule(rule)->styleRule()->properties(), document);
        } else if (rule->type() == CSSRule::STYLE_RULE) {
            retrieveResourcesForProperties(toCSSStyleRule(rule)->styleRule()->properties(), document);
        }
    }

    if (url.isValid() && !m_resourceURLs.contains(url)) {
        WTF::TextEncoding textEncoding(styleSheet->contents()->charset());
        ASSERT(textEncoding.isValid());
        String textString = cssText.toString();
        CString text = textEncoding.normalizeAndEncode(textString, WTF::EntitiesForUnencodables);
        m_resources->append(SerializedResource(url, String("text/css"), SharedBuffer::create(text.data(), text.length())));
        m_resourceURLs.add(url);
    }
}
