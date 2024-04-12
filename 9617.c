static bool is_valid_NPEvent_type(NPEvent *event)
{
  switch (event->type) {
  case GraphicsExpose:
  case FocusIn:
  case FocusOut:
  case EnterNotify:
  case LeaveNotify:
  case MotionNotify:
  case ButtonPress:
  case ButtonRelease:
  case KeyPress:
  case KeyRelease:
	return true;
  default:
	break;
  }
  return false;
}
