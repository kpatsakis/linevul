void StyleResolver::applyPropertiesToStyle(const CSSPropertyValue* properties, size_t count, RenderStyle* style)
{
    StyleResolverState state(document(), document().documentElement(), style);
    state.setStyle(style);

    state.fontBuilder().initForStyleResolve(document(), style, state.useSVGZoomRules());

    for (size_t i = 0; i < count; ++i) {
        if (properties[i].value) {
            switch (properties[i].property) {
            case CSSPropertyFontSize:
            case CSSPropertyLineHeight:
                updateFont(state);
                break;
            default:
                break;
            }
            StyleBuilder::applyProperty(properties[i].property, state, properties[i].value);
        }
    }
}
