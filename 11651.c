    RVHObserver(RenderViewHostObserverArray* parent, RenderViewHost* rvh)
        : RenderViewHostObserver(rvh),
          parent_(parent) {
    }
