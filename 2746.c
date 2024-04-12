void AutofillManager::OnDidFillAutofillFormData() {
  NotificationService::current()->Notify(
      NotificationType::AUTOFILL_DID_FILL_FORM_DATA,
      Source<RenderViewHost>(tab_contents()->render_view_host()),
      NotificationService::NoDetails());
}
