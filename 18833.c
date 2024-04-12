static int create_window(PluginInstance *plugin, NPWindow *window)
{
  if (plugin->is_windowless) {
	destroy_window_attributes(plugin->window.ws_info);
	plugin->window.ws_info = NULL;
  }
  assert(plugin->window.ws_info == NULL);

  NPSetWindowCallbackStruct *ws_info;
  if ((ws_info = NPW_MemClone(NPSetWindowCallbackStruct, window->ws_info)) == NULL)
	return -1;
  if (create_window_attributes(ws_info) < 0)
	return -1;
  memcpy(&plugin->window, window, sizeof(*window));
  window = &plugin->window;
  window->ws_info = ws_info;
  fixup_size_hints(plugin);

  if (plugin->is_windowless)
	return 0;

  if (plugin->use_xembed) {
	GtkData *toolkit = calloc(1, sizeof(*toolkit));
	if (toolkit == NULL)
	  return -1;
	toolkit->container = gtk_plug_new((GdkNativeWindow)window->window);
	if (toolkit->container == NULL)
	  return -1;
	gtk_widget_set_size_request(toolkit->container, window->width, window->height); 
	gtk_widget_show(toolkit->container);
	toolkit->socket = gtk_socket_new();
	if (toolkit->socket == NULL)
	  return -1;
	gtk_widget_show(toolkit->socket);
	gtk_container_add(GTK_CONTAINER(toolkit->container), toolkit->socket);
	gtk_widget_show_all(toolkit->container);
	window->window = (void *)gtk_socket_get_id(GTK_SOCKET(toolkit->socket));
	plugin->toolkit_data = toolkit;
#if USE_XEMBED_HACK
	g_signal_connect(toolkit->container, "delete-event",
					 G_CALLBACK(gtk_true), NULL);
#endif
	g_signal_connect(toolkit->container, "destroy",
					 G_CALLBACK(gtk_widget_destroyed), &toolkit->container);
	g_signal_connect(toolkit->socket, "plug_removed",
					 G_CALLBACK(gtk_true), NULL);
	return 0;
  }

  XtData *toolkit = calloc(1, sizeof(*toolkit));
  if (toolkit == NULL)
	return -1;

  String app_name, app_class;
  XtGetApplicationNameAndClass(x_display, &app_name, &app_class);
  Widget top_widget = XtVaAppCreateShell("drawingArea", app_class, topLevelShellWidgetClass, x_display,
										 XtNoverrideRedirect, True,
										 XtNborderWidth, 0,
										 XtNbackgroundPixmap, None,
										 XtNwidth, window->width,
										 XtNheight, window->height,
										 NULL);

  Widget form = XtVaCreateManagedWidget("form", compositeWidgetClass, top_widget,
										XtNdepth, ws_info->depth,
										XtNvisual, ws_info->visual,
										XtNcolormap, ws_info->colormap,
										XtNborderWidth, 0,
										XtNbackgroundPixmap, None,
										XtNwidth, window->width,
										XtNheight, window->height,
										NULL);

  XtRealizeWidget(top_widget);
  XReparentWindow(x_display, XtWindow(top_widget), (Window)window->window, 0, 0);
  XtRealizeWidget(form);

  XSelectInput(x_display, XtWindow(top_widget), 0x0fffff);
  XtAddEventHandler(top_widget, (SubstructureNotifyMask|KeyPress|KeyRelease), True, xt_client_event_handler, toolkit);
  XtAddEventHandler(form, (ButtonReleaseMask), True, xt_client_event_handler, toolkit);
  xt_client_set_info(form, 0);

  plugin->toolkit_data = toolkit;
  toolkit->top_widget = top_widget;
  toolkit->form = form;
  toolkit->browser_window = (Window)window->window;
  window->window = (void *)XtWindow(form);
  return 0;
}
