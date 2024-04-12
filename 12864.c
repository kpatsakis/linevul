void BuildMouseWheelEvent(const WebInputEvent* event, NPPepperEvent* npevent) {
  const WebMouseWheelEvent* mouse_wheel_event =
      reinterpret_cast<const WebMouseWheelEvent*>(event);
  npevent->u.wheel.modifier = mouse_wheel_event->modifiers;
  npevent->u.wheel.deltaX = mouse_wheel_event->deltaX;
  npevent->u.wheel.deltaY = mouse_wheel_event->deltaY;
  npevent->u.wheel.wheelTicksX = mouse_wheel_event->wheelTicksX;
  npevent->u.wheel.wheelTicksY = mouse_wheel_event->wheelTicksY;
  npevent->u.wheel.scrollByPage = mouse_wheel_event->scrollByPage;
}
