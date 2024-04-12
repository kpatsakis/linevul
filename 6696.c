void RenderView::StartPluginIme() {
  IPC::Message* msg = new ViewHostMsg_StartPluginIme(routing_id());
  msg->set_unblock(true);
  Send(msg);
}
