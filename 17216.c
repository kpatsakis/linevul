DragController::DragController(Page* page)
    : page_(page),
      document_under_mouse_(nullptr),
      drag_initiator_(nullptr),
      file_input_element_under_mouse_(nullptr),
      document_is_handling_drag_(false),
      drag_destination_action_(kDragDestinationActionNone),
      did_initiate_drag_(false) {}
