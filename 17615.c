  ContextMenuMessageDispatcher(
      int render_process_id,
      const ViewHostMsg_ContextMenu& context_menu_message)
      : render_process_id_(render_process_id),
        context_menu_message_(context_menu_message) {
  }
