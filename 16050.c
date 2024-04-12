void RenderView::OnAccessibilityDoDefaultAction(int acc_obj_id) {
  if (!accessibility_.get())
    return;

  WebAccessibilityObject obj = accessibility_->getObjectById(acc_obj_id);
  if (!obj.isValid())
    return;

  obj.performDefaultAction();
}
