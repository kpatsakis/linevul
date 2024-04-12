static void xt_client_event_handler(Widget w, XtPointer client_data, XEvent *event, Boolean *cont)
{
  XtData *toolkit = (XtData *)client_data;

  switch (event->type) {
  case ClientMessage:
	if (event->xclient.message_type == XInternAtom(x_display, "_XEMBED", False)) {
	  switch (event->xclient.data.l[1]) {
	  case XEMBED_FOCUS_IN:
		xt_client_simulate_focus(toolkit->form, FocusIn);
		break;
	  case XEMBED_FOCUS_OUT:
		xt_client_simulate_focus(toolkit->form, FocusOut);
		break;
	  }
	}
	break;
  case KeyPress:
  case KeyRelease:
	if (event->xkey.window == XtWindow(toolkit->top_widget)) {
	  event->xkey.window = XtWindow(toolkit->form);
	  trap_errors();
	  XSendEvent(XtDisplay(toolkit->form), event->xfocus.window, False, NoEventMask, event);
	  XSync(XtDisplay(toolkit->form), False);
	  untrap_errors();
	  *cont = False;
	}
	break;
  case ButtonRelease:
	send_xembed_message(XtDisplay(w), toolkit->browser_window, XEMBED_REQUEST_FOCUS, 0, 0, 0);
	break;
  }
}
