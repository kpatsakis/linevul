bool Browser::PreHandleGestureEvent(content::WebContents* source,
                                    const blink::WebGestureEvent& event) {
#if defined(OS_MACOSX)
  if (event.GetType() == blink::WebInputEvent::kGestureDoubleTap) {
    content::BrowserPluginGuestManager* guest_manager =
        source->GetBrowserContext()->GetGuestManager();
    if (guest_manager) {
      const content::WebContents* guest_contents =
          guest_manager->GetFullPageGuest(source);
      if (guest_contents) {
        const extensions::Extension* extension =
            extensions::ProcessManager::Get(guest_contents->GetBrowserContext())
                ->GetExtensionForWebContents(guest_contents);
        if (extension && extension->id() == extension_misc::kPdfExtensionId)
          return true;
      }
    }
  }
#endif  // defined(OS_MACOSX)

  if (app_name() == DevToolsWindow::kDevToolsApp)
    return blink::WebInputEvent::IsPinchGestureEventType(event.GetType());
  return false;
}
