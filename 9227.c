void StyleResolver::applyAnimatedProperties(StyleResolverState& state, const AnimationEffect::CompositableValueMap& compositableValues)
{
    ASSERT(RuntimeEnabledFeatures::webAnimationsCSSEnabled());
    ASSERT(pass != VariableDefinitions);
    ASSERT(pass != AnimationProperties);

    for (AnimationEffect::CompositableValueMap::const_iterator iter = compositableValues.begin(); iter != compositableValues.end(); ++iter) {
        CSSPropertyID property = iter->key;
        if (!isPropertyForPass<pass>(property))
            continue;
        ASSERT_WITH_MESSAGE(!iter->value->dependsOnUnderlyingValue(), "Web Animations not yet implemented: An interface for compositing onto the underlying value.");
        RefPtr<AnimatableValue> animatableValue = iter->value->compositeOnto(0);
        AnimatedStyleBuilder::applyProperty(property, state, animatableValue.get());
    }
}
