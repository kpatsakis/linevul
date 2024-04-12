void MessageService::PendingOpenChannel(scoped_ptr<OpenChannelParams> params,
                                        int source_process_id,
                                        ExtensionHost* host) {
  if (!host)
    return;  // TODO(mpcomplete): notify source of disconnect?

  content::RenderProcessHost* source =
      content::RenderProcessHost::FromID(source_process_id);
  if (!source)
    return;

  params->source = source;
  params->receiver.reset(new ExtensionMessagePort(host->render_process_host(),
                                                  MSG_ROUTING_CONTROL,
                                                  params->target_extension_id));
  OpenChannelImpl(params.Pass());
}
