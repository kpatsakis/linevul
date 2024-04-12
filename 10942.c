bool FrameView::contentsInCompositedLayer() const
{
    RenderView* renderView = this->renderView();
    if (renderView && renderView->compositingState() == PaintsIntoOwnBacking) {
        GraphicsLayer* layer = renderView->layer()->compositedLayerMapping()->mainGraphicsLayer();
        if (layer && layer->drawsContent())
            return true;
    }

    return false;
}
