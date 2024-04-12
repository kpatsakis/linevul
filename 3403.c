void LocalDOMWindow::print(ScriptState* script_state) {
  if (!GetFrame())
    return;

  Page* page = GetFrame()->GetPage();
  if (!page)
    return;

  if (script_state &&
      v8::MicrotasksScope::IsRunningMicrotasks(script_state->GetIsolate())) {
    UseCounter::Count(document(), WebFeature::kDuring_Microtask_Print);
  }

  if (GetFrame()->IsLoading()) {
    should_print_when_finished_loading_ = true;
    return;
  }

  UseCounter::CountCrossOriginIframe(*document(),
                                     WebFeature::kCrossOriginWindowPrint);

  should_print_when_finished_loading_ = false;
  page->GetChromeClient().Print(GetFrame());
}
