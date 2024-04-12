void PasswordAutofillAgent::DidStartProvisionalLoad() {
  std::unique_ptr<RendererSavePasswordProgressLogger> logger;
  if (logging_state_active_) {
    logger.reset(new RendererSavePasswordProgressLogger(this, routing_id()));
    logger->LogMessage(Logger::STRING_DID_START_PROVISIONAL_LOAD_METHOD);
  }

  const blink::WebLocalFrame* navigated_frame = render_frame()->GetWebFrame();
  if (navigated_frame->parent()) {
    if (logger)
      logger->LogMessage(Logger::STRING_FRAME_NOT_MAIN_FRAME);
    return;
  }

  content::DocumentState* document_state =
      content::DocumentState::FromDataSource(
          navigated_frame->provisionalDataSource());
  content::NavigationState* navigation_state =
      document_state->navigation_state();
  ui::PageTransition type = navigation_state->GetTransitionType();
  if (ui::PageTransitionIsWebTriggerable(type) &&
      ui::PageTransitionIsNewNavigation(type) &&
      !blink::WebUserGestureIndicator::isProcessingUserGesture()) {
    if (provisionally_saved_form_) {
      if (logger) {
        logger->LogPasswordForm(
            Logger::STRING_PROVISIONALLY_SAVED_FORM_FOR_FRAME,
            *provisionally_saved_form_);
      }
      Send(new AutofillHostMsg_PasswordFormSubmitted(
          routing_id(), *provisionally_saved_form_));
      provisionally_saved_form_.reset();
    } else {
      ScopedVector<PasswordForm> possible_submitted_forms;
      blink::WebVector<blink::WebFormElement> forms;
      render_frame()->GetWebFrame()->document().forms(forms);

      bool password_forms_found = false;
      for (size_t i = 0; i < forms.size(); ++i) {
        blink::WebFormElement form_element = forms[i];
        if (logger) {
          LogHTMLForm(logger.get(), Logger::STRING_FORM_FOUND_ON_PAGE,
                      form_element);
        }
        possible_submitted_forms.push_back(CreatePasswordFormFromWebForm(
            form_element, &nonscript_modified_values_, &form_predictions_));
      }

      possible_submitted_forms.push_back(
          CreatePasswordFormFromUnownedInputElements(
              *render_frame()->GetWebFrame(),
              &nonscript_modified_values_,
              &form_predictions_));

      for (const PasswordForm* password_form : possible_submitted_forms) {
        if (password_form && !password_form->username_value.empty() &&
            FormContainsNonDefaultPasswordValue(*password_form)) {
          password_forms_found = true;
          if (logger) {
            logger->LogPasswordForm(Logger::STRING_PASSWORD_FORM_FOUND_ON_PAGE,
                                    *password_form);
          }
          Send(new AutofillHostMsg_PasswordFormSubmitted(routing_id(),
                                                         *password_form));
          break;
        }
      }

      if (!password_forms_found && logger)
        logger->LogMessage(Logger::STRING_PASSWORD_FORM_NOT_FOUND_ON_PAGE);
    }
  }

  gatekeeper_.Reset();
}
