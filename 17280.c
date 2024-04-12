  static gboolean OnCrossingEvent(GtkWidget* widget,
                                  GdkEventCrossing* event,
                                  RenderWidgetHostViewGtk* host_view) {
    TRACE_EVENT0("browser",
                 "RenderWidgetHostViewGtkWidget::OnCrossingEvent");
    const int any_button_mask =
        GDK_BUTTON1_MASK |
        GDK_BUTTON2_MASK |
        GDK_BUTTON3_MASK |
        GDK_BUTTON4_MASK |
        GDK_BUTTON5_MASK;

    if (!(event->state & any_button_mask)) {
      WebKit::WebMouseEvent mouse_event =
          WebInputEventFactory::mouseEvent(event);
      host_view->ModifyEventMovementAndCoords(&mouse_event);
      mouse_event.movementX = 0;
      mouse_event.movementY = 0;
      RenderWidgetHostImpl::From(
          host_view->GetRenderWidgetHost())->ForwardMouseEvent(mouse_event);
    }

    return FALSE;
  }
