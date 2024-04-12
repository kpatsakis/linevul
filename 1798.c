WebContentsViewAura::WebContentsViewAura(
    WebContentsImpl* web_contents,
    WebContentsViewDelegate* delegate)
    : web_contents_(web_contents),
      delegate_(delegate),
      current_drag_op_(blink::WebDragOperationNone),
      drag_dest_delegate_(NULL),
      current_rvh_for_drag_(NULL),
      overscroll_change_brightness_(false),
      current_overscroll_gesture_(OVERSCROLL_NONE),
      completed_overscroll_gesture_(OVERSCROLL_NONE),
      touch_editable_(TouchEditableImplAura::Create()) {
}
