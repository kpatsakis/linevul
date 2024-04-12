MouseEventWithHitTestResults Document::prepareMouseEvent(const HitTestRequest& request, const LayoutPoint& documentPoint, const PlatformMouseEvent& event)
{
    DCHECK(!layoutView() || layoutView()->isLayoutView());

    if (!layoutView() || !view() || !view()->didFirstLayout())
        return MouseEventWithHitTestResults(event, HitTestResult(request, LayoutPoint()));

    HitTestResult result(request, documentPoint);
    layoutView()->hitTest(result);

    if (!request.readOnly())
        updateHoverActiveState(request, result.innerElement());

    if (isHTMLCanvasElement(result.innerNode())) {
        PlatformMouseEvent eventWithRegion = event;
        std::pair<Element*, String> regionInfo = toHTMLCanvasElement(result.innerNode())->getControlAndIdIfHitRegionExists(result.pointInInnerNodeFrame());
        if (regionInfo.first)
            result.setInnerNode(regionInfo.first);
        eventWithRegion.setRegion(regionInfo.second);
        return MouseEventWithHitTestResults(eventWithRegion, result);
    }

    return MouseEventWithHitTestResults(event, result);
}
