  static gboolean OnButtonPressReleaseEvent(
      GtkWidget* widget,
      GdkEventButton* event,
      RenderWidgetHostViewGtk* host_view) {
    TRACE_EVENT0("browser",
                 "RenderWidgetHostViewGtkWidget::OnButtonPressReleaseEvent");

    if (event->type != GDK_BUTTON_RELEASE)
      host_view->set_last_mouse_down(event);

    if (!(event->button == 1 || event->button == 2 || event->button == 3))
      return FALSE;  // We do not forward any other buttons to the renderer.
    if (event->type == GDK_2BUTTON_PRESS || event->type == GDK_3BUTTON_PRESS)
      return FALSE;

    if (!gtk_widget_is_focus(widget))
      host_view->host_->OnPointerEventActivate();

    if (event->type != GDK_BUTTON_RELEASE)
      host_view->im_context_->ConfirmComposition();

    GtkWidget* event_widget = gtk_get_event_widget(
        reinterpret_cast<GdkEvent*>(event));
    if (event_widget != widget) {
      int x = 0;
      int y = 0;
      gtk_widget_get_pointer(widget, &x, &y);
      GtkAllocation allocation;
      gtk_widget_get_allocation(widget, &allocation);
      bool click_in_popup = x >= 0 && y >= 0 && x < allocation.width &&
          y < allocation.height;
      if (event->type != GDK_BUTTON_RELEASE && host_view->IsPopup() &&
          !host_view->is_popup_first_mouse_release_ && !click_in_popup) {
        host_view->host_->Shutdown();
        return FALSE;
      }
      event->x = x;
      event->y = y;
    }

    if (event->type == GDK_BUTTON_PRESS && !gtk_widget_has_focus(widget))
      gtk_widget_grab_focus(widget);

    host_view->is_popup_first_mouse_release_ = false;
    RenderWidgetHostImpl* widget_host =
        RenderWidgetHostImpl::From(host_view->GetRenderWidgetHost());
    if (widget_host)
      widget_host->ForwardMouseEvent(WebInputEventFactory::mouseEvent(event));

    return FALSE;
  }
