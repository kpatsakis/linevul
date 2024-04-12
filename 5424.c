static const AtomicString& orientationToString(blink::WebScreenOrientation orientation)
{
    unsigned length = 0;
    ScreenOrientationInfo* orientationMap = orientationsMap(length);
    for (unsigned i = 0; i < length; ++i) {
        if (orientationMap[i].orientation == orientation)
            return orientationMap[i].name;
    }
    ASSERT_NOT_REACHED();
    return nullAtom;
}
