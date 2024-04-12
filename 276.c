QVector2D QQuickWebViewPrivate::FlickableAxisLocker::touchVelocity(const QTouchEvent* event)
{
    static bool touchVelocityAvailable = event->device()->capabilities().testFlag(QTouchDevice::Velocity);
    const QTouchEvent::TouchPoint& touchPoint = event->touchPoints().first();

    if (touchVelocityAvailable)
        return touchPoint.velocity();

    const QLineF movementLine(touchPoint.pos(), m_initialPosition);
    const ulong elapsed = event->timestamp() - m_time;

    if (!elapsed)
        return QVector2D(0, 0);

    return QVector2D(1000 * movementLine.dx() / elapsed, 1000 * movementLine.dy() / elapsed);
}
