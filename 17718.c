adjust_exit_policy_from_exitpolicy_failure(origin_circuit_t *circ,
                                           entry_connection_t *conn,
                                           node_t *node,
                                           const tor_addr_t *addr)
{
  int make_reject_all = 0;
  const sa_family_t family = tor_addr_family(addr);

  if (node) {
    tor_addr_t tmp;
    int asked_for_family = tor_addr_parse(&tmp, conn->socks_request->address);
    if (family == AF_UNSPEC) {
      make_reject_all = 1;
    } else if (node_exit_policy_is_exact(node, family) &&
               asked_for_family != -1 && !conn->chosen_exit_name) {
      make_reject_all = 1;
    }

    if (make_reject_all) {
      log_info(LD_APP,
               "Exitrouter %s seems to be more restrictive than its exit "
               "policy. Not using this router as exit for now.",
               node_describe(node));
      policies_set_node_exitpolicy_to_reject_all(node);
    }
  }

  if (family != AF_UNSPEC)
    addr_policy_append_reject_addr(&circ->prepend_policy, addr);
}
