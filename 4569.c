void ImageInputType::setUseFallbackContent()
{
    if (m_useFallbackContent)
        return;
    m_useFallbackContent = true;
    if (element().document().inStyleRecalc())
        return;
    if (ShadowRoot* root = element().userAgentShadowRoot())
        root->removeChildren();
    createShadowSubtree();
}
