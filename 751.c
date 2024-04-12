bool SVGLayoutSupport::pointInClippingArea(const LayoutObject* object, const FloatPoint& point)
{
    ASSERT(object);

    SVGResources* resources = SVGResourcesCache::cachedResourcesForLayoutObject(object);
    if (!resources)
        return true;

    if (LayoutSVGResourceClipper* clipper = resources->clipper())
        return clipper->hitTestClipContent(object->objectBoundingBox(), point);

    return true;
}
