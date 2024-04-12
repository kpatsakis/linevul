static void RunAutofocusTask(ExecutionContext* context) {
  if (!context)
    return;

  Document* document = To<Document>(context);
  if (Element* element = document->AutofocusElement()) {
    document->SetAutofocusElement(nullptr);
    element->focus();
  }
}
