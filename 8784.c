proto_reg_handoff_rpcap (void)
{
  static gboolean rpcap_prefs_initialized = FALSE;

  if (!rpcap_prefs_initialized) {
    data_handle = find_dissector ("data");
    rpcap_prefs_initialized = TRUE;

    heur_dissector_add ("tcp", dissect_rpcap_heur_tcp, "RPCAP over TCP", "rpcap_tcp", proto_rpcap, HEURISTIC_ENABLE);
    heur_dissector_add ("udp", dissect_rpcap_heur_udp, "RPCAP over UDP", "rpcap_udp", proto_rpcap, HEURISTIC_ENABLE);
  }

  info_added = FALSE;
  linktype = global_linktype;
}
