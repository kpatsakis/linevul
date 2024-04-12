FloatPoint AffineTransform::mapPoint(const FloatPoint& point) const
{
    double x2, y2;
    map(point.x(), point.y(), x2, y2);

    return FloatPoint(narrowPrecisionToFloat(x2), narrowPrecisionToFloat(y2));
}
