bool ContainerNode::getLowerRightCorner(FloatPoint& point) const
{
    if (!layoutObject())
        return false;

    LayoutObject* o = layoutObject();
    if (!o->isInline() || o->isReplaced()) {
        LayoutBox* box = toLayoutBox(o);
        point = o->localToAbsolute(FloatPoint(box->size()), UseTransforms);
        return true;
    }

    LayoutObject* startContinuation = nullptr;
    while (o) {
        if (LayoutObject* oLastChild = o->slowLastChild()) {
            o = oLastChild;
        } else if (o != layoutObject() && o->previousSibling()) {
            o = o->previousSibling();
        } else {
            LayoutObject* prev = nullptr;
            while (!prev) {
                if (startContinuation == o) {
                    startContinuation = nullptr;
                } else if (!startContinuation) {
                    if (LayoutObject* continuation = endOfContinuations(o)) {
                        startContinuation = o;
                        prev = continuation;
                        break;
                    }
                }
                if (o == layoutObject()) {
                    return false;
                }
                o = o->parent();
                if (!o)
                    return false;
                prev = o->previousSibling();
            }
            o = prev;
        }
        ASSERT(o);
        if (o->isText() || o->isReplaced()) {
            point = FloatPoint();
            if (o->isText()) {
                LayoutText* text = toLayoutText(o);
                IntRect linesBox = text->linesBoundingBox();
                if (!linesBox.maxX() && !linesBox.maxY())
                    continue;
                point.moveBy(linesBox.maxXMaxYCorner());
                point = o->localToAbsolute(point, UseTransforms);
            } else {
                LayoutBox* box = toLayoutBox(o);
                point.moveBy(box->frameRect().maxXMaxYCorner());
                point = o->container()->localToAbsolute(point, UseTransforms);
            }
            return true;
        }
    }
    return true;
}
