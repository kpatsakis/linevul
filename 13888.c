bool SVGAnimateElement::isAdditive() const
{
    if (animationMode() == ByAnimation || animationMode() == FromByAnimation)
        if (!animatedPropertyTypeSupportsAddition())
            return false;

    return SVGAnimationElement::isAdditive();
}
