FloatSize AffineTransform::mapSize(const FloatSize& size) const
{
    double width2 = size.width() * xScale();
    double height2 = size.height() * yScale();

    return FloatSize(narrowPrecisionToFloat(width2), narrowPrecisionToFloat(height2));
}
