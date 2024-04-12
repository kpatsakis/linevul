void RenderWidgetHostViewAura::TextInputStateChanged(
    const ViewHostMsg_TextInputState_Params& params) {
  if (text_input_type_ != params.type ||
      can_compose_inline_ != params.can_compose_inline) {
    text_input_type_ = params.type;
    can_compose_inline_ = params.can_compose_inline;
    if (GetInputMethod())
      GetInputMethod()->OnTextInputTypeChanged(this);
  }
}
