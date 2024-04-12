static inline IntPoint roundTransformedPoint(const FloatPoint &point)
{
    return IntPoint(static_cast<int>(floorf(point.x())), static_cast<int>(floorf(point.y())));
}
