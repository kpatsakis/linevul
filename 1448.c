void InspectorCSSOMWrappers::collectFromStyleSheetContents(HashSet<RefPtr<CSSStyleSheet> >& sheetWrapperSet, StyleSheetContents* styleSheet)
{
    if (!styleSheet)
        return;
    RefPtr<CSSStyleSheet> styleSheetWrapper = CSSStyleSheet::create(styleSheet);
    sheetWrapperSet.add(styleSheetWrapper);
    collect(styleSheetWrapper.get());
}
