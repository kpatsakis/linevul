void WebPageProxy::didReceiveEvent(uint32_t opaqueType, bool handled)
{
    WebEvent::Type type = static_cast<WebEvent::Type>(opaqueType);

    switch (type) {
    case WebEvent::NoType:
    case WebEvent::MouseMove:
        break;

    case WebEvent::MouseDown:
    case WebEvent::MouseUp:
    case WebEvent::Wheel:
    case WebEvent::KeyDown:
    case WebEvent::KeyUp:
    case WebEvent::RawKeyDown:
    case WebEvent::Char:
#if ENABLE(GESTURE_EVENTS)
    case WebEvent::GestureScrollBegin:
    case WebEvent::GestureScrollEnd:
#endif
        process()->responsivenessTimer()->stop();
        break;
    }

    switch (type) {
    case WebEvent::NoType:
        break;
    case WebEvent::MouseMove:
        m_processingMouseMoveEvent = false;
        if (m_nextMouseMoveEvent) {
            handleMouseEvent(*m_nextMouseMoveEvent);
            m_nextMouseMoveEvent = nullptr;
        }
        break;
    case WebEvent::MouseDown:
    case WebEvent::MouseUp:
#if ENABLE(GESTURE_EVENTS)
    case WebEvent::GestureScrollBegin:
    case WebEvent::GestureScrollEnd:
#endif
        break;

    case WebEvent::Wheel: {
        m_processingWheelEvent = false;
        if (m_nextWheelEvent) {
            handleWheelEvent(*m_nextWheelEvent);
            m_nextWheelEvent = nullptr;
        }
        break;
    }

    case WebEvent::KeyDown:
    case WebEvent::KeyUp:
    case WebEvent::RawKeyDown:
    case WebEvent::Char: {
        NativeWebKeyboardEvent event = m_keyEventQueue.first();
        MESSAGE_CHECK(type == event.type());

        m_keyEventQueue.removeFirst();

        m_pageClient->doneWithKeyEvent(event, handled);

        if (handled)
            break;

        m_uiClient.didNotHandleKeyEvent(this, event);
        break;
    }
    }
}
