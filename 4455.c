bool AffineTransform::decompose(DecomposedType& decomp) const
{
    AffineTransform m(*this);

    double sx = xScale();
    double sy = yScale();

    if (m.a() * m.d() - m.c() * m.b() < 0) {
        if (m.a() < m.d())
            sx = -sx;
        else
            sy = -sy;
    }

    m.scale(1 / sx, 1 / sy);

    double angle = atan2(m.b(), m.a());

    m.rotateRadians(-angle);

    decomp.scaleX = sx;
    decomp.scaleY = sy;
    decomp.angle = angle;
    decomp.remainderA = m.a();
    decomp.remainderB = m.b();
    decomp.remainderC = m.c();
    decomp.remainderD = m.d();
    decomp.translateX = m.e();
    decomp.translateY = m.f();

    return true;
}
