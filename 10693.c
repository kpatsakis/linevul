  static MockRenderWidgetHostImpl* Create(RenderWidgetHostDelegate* delegate,
                                          RenderProcessHost* process,
                                          int32_t routing_id) {
    mojom::WidgetPtr widget;
    std::unique_ptr<MockWidgetImpl> widget_impl =
        std::make_unique<MockWidgetImpl>(mojo::MakeRequest(&widget));

    return new MockRenderWidgetHostImpl(delegate, process, routing_id,
                                        std::move(widget_impl),
                                        std::move(widget));
  }
