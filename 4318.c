  void GetTouchActionsForChild(
      RenderWidgetHostInputEventRouter* router,
      RenderWidgetHostViewBase* rwhv_root,
      RenderWidgetHostViewBase* rwhv_child,
      const gfx::Point& event_position,
      base::Optional<cc::TouchAction>& effective_touch_action,
      base::Optional<cc::TouchAction>& whitelisted_touch_action) {
    InputEventAckWaiter ack_observer(
        rwhv_child->GetRenderWidgetHost(),
        base::BindRepeating([](content::InputEventAckSource source,
                               content::InputEventAckState state,
                               const blink::WebInputEvent& event) {
          return event.GetType() == blink::WebGestureEvent::kTouchStart ||
                 event.GetType() == blink::WebGestureEvent::kTouchMove ||
                 event.GetType() == blink::WebGestureEvent::kTouchEnd;
        }));

    InputRouterImpl* input_router = static_cast<InputRouterImpl*>(
        static_cast<RenderWidgetHostImpl*>(rwhv_child->GetRenderWidgetHost())
            ->input_router());
    input_router->touch_action_filter_.allowed_touch_action_.reset();
    input_router->touch_action_filter_.white_listed_touch_action_.reset();
    ack_observer.Reset();
    SyntheticWebTouchEvent touch_event;
    int index = touch_event.PressPoint(event_position.x(), event_position.y());
    router->RouteTouchEvent(rwhv_root, &touch_event,
                            ui::LatencyInfo(ui::SourceEventType::TOUCH));
    ack_observer.Wait();
    effective_touch_action =
        input_router->touch_action_filter_.allowed_touch_action_;
    whitelisted_touch_action =
        input_router->touch_action_filter_.white_listed_touch_action_;

    ack_observer.Reset();
    touch_event.MovePoint(index, 1, 1);
    router->RouteTouchEvent(rwhv_root, &touch_event,
                            ui::LatencyInfo(ui::SourceEventType::TOUCH));
    ack_observer.Wait();

    ack_observer.Reset();
    touch_event.ReleasePoint(index);
    router->RouteTouchEvent(rwhv_root, &touch_event,
                            ui::LatencyInfo(ui::SourceEventType::TOUCH));
    ack_observer.Wait();
  }
