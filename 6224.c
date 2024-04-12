void StyleResolver::collectViewportRules()
{
    viewportStyleResolver()->collectViewportRules(CSSDefaultStyleSheets::defaultStyle, ViewportStyleResolver::UserAgentOrigin);

    if (document().isMobileDocument())
        viewportStyleResolver()->collectViewportRules(CSSDefaultStyleSheets::xhtmlMobileProfileStyle(), ViewportStyleResolver::UserAgentOrigin);

    if (ScopedStyleResolver* scopedResolver = m_styleTree.scopedStyleResolverForDocument())
        scopedResolver->collectViewportRulesTo(this);

    viewportStyleResolver()->resolve();
}
