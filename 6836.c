void SelectionController::SelectClosestMisspellingFromMouseEvent(
    const MouseEventWithHitTestResults& result) {
  if (!mouse_down_may_start_select_)
    return;

  SelectClosestMisspellingFromHitTestResult(
      result.GetHitTestResult(),
      (result.Event().click_count == 2 &&
       frame_->GetEditor().IsSelectTrailingWhitespaceEnabled())
          ? AppendTrailingWhitespace::kShouldAppend
          : AppendTrailingWhitespace::kDontAppend);
}
