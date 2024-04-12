void setAnimationUpdateIfNeeded(StyleResolverState& state, Element& element)
{
    if (RuntimeEnabledFeatures::webAnimationsCSSEnabled() && state.animationUpdate())
        element.ensureActiveAnimations()->cssAnimations().setPendingUpdate(state.takeAnimationUpdate());
}
