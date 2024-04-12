void StyleResolver::updateFont(StyleResolverState& state)
{
    state.fontBuilder().createFont(m_fontSelector, state.parentStyle(), state.style());
}
