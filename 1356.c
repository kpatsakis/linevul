void HTMLFormElement::Submit(Event* event,
                             HTMLFormControlElement* submit_button) {
  LocalFrameView* view = GetDocument().View();
  LocalFrame* frame = GetDocument().GetFrame();
  if (!view || !frame || !frame->GetPage())
    return;

  if (!isConnected()) {
    GetDocument().AddConsoleMessage(ConsoleMessage::Create(
        kJSMessageSource, kWarningMessageLevel,
        "Form submission canceled because the form is not connected"));
    return;
  }

  if (is_submitting_)
    return;

  EventQueueScope scope_for_dialog_close;
  AutoReset<bool> submit_scope(&is_submitting_, true);

  if (event && !submit_button) {
    for (const auto& listed_element : ListedElements()) {
      if (!listed_element->IsFormControlElement())
        continue;
      HTMLFormControlElement* control =
          ToHTMLFormControlElement(listed_element);
      DCHECK(!control->IsActivatedSubmit());
      if (control->IsSuccessfulSubmitButton()) {
        submit_button = control;
        break;
      }
    }
  }

  FormSubmission* form_submission =
      FormSubmission::Create(this, attributes_, event, submit_button);
  if (form_submission->Method() == FormSubmission::kDialogMethod) {
    SubmitDialog(form_submission);
  } else if (in_user_js_submit_event_) {
    planned_navigation_ = form_submission;
  } else {
    ScheduleFormSubmission(form_submission);
  }
}
