dissect_rpcap_startcap_request (tvbuff_t *tvb, packet_info *pinfo,
                                proto_tree *parent_tree, gint offset)
{
  proto_tree *tree, *field_tree;
  proto_item *ti, *field_ti;
  guint16 flags;

  ti = proto_tree_add_item (parent_tree, hf_startcap_request, tvb, offset, -1, ENC_NA);
  tree = proto_item_add_subtree (ti, ett_startcap_request);

  proto_tree_add_item (tree, hf_snaplen, tvb, offset, 4, ENC_BIG_ENDIAN);
  offset += 4;

  proto_tree_add_item (tree, hf_read_timeout, tvb, offset, 4, ENC_BIG_ENDIAN);
  offset += 4;

  flags = tvb_get_ntohs (tvb, offset);
  field_ti = proto_tree_add_uint_format (tree, hf_flags, tvb, offset, 2, flags, "Flags");
  field_tree = proto_item_add_subtree (field_ti, ett_startcap_flags);
  proto_tree_add_item (field_tree, hf_flags_promisc, tvb, offset, 2, ENC_BIG_ENDIAN);
  proto_tree_add_item (field_tree, hf_flags_dgram, tvb, offset, 2, ENC_BIG_ENDIAN);
  proto_tree_add_item (field_tree, hf_flags_serveropen, tvb, offset, 2, ENC_BIG_ENDIAN);
  proto_tree_add_item (field_tree, hf_flags_inbound, tvb, offset, 2, ENC_BIG_ENDIAN);
  proto_tree_add_item (field_tree, hf_flags_outbound, tvb, offset, 2, ENC_BIG_ENDIAN);

  if (flags & 0x1F) {
    gchar *flagstr = wmem_strdup_printf (wmem_packet_scope(), "%s%s%s%s%s",
          (flags & FLAG_PROMISC)    ? ", Promiscuous" : "",
          (flags & FLAG_DGRAM)      ? ", Datagram"    : "",
          (flags & FLAG_SERVEROPEN) ? ", ServerOpen"  : "",
          (flags & FLAG_INBOUND)    ? ", Inbound"     : "",
          (flags & FLAG_OUTBOUND)   ? ", Outbound"    : "");
    proto_item_append_text (field_ti, ":%s", &flagstr[1]);
  } else {
    proto_item_append_text (field_ti, " (none)");
  }
  offset += 2;

  proto_tree_add_item (tree, hf_client_port, tvb, offset, 2, ENC_BIG_ENDIAN);
  offset += 2;

  dissect_rpcap_filter (tvb, pinfo, tree, offset);
}
