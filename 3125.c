ofpact_check__(enum ofputil_protocol *usable_protocols, struct ofpact *a,
               struct flow *flow, ofp_port_t max_ports,
               uint8_t table_id, uint8_t n_tables)
{
    const struct ofpact_enqueue *enqueue;
    const struct mf_field *mf;

    switch (a->type) {
    case OFPACT_OUTPUT:
        return ofpact_check_output_port(ofpact_get_OUTPUT(a)->port,
                                        max_ports);

    case OFPACT_CONTROLLER:
        return 0;

    case OFPACT_ENQUEUE:
        enqueue = ofpact_get_ENQUEUE(a);
        if (ofp_to_u16(enqueue->port) >= ofp_to_u16(max_ports)
            && enqueue->port != OFPP_IN_PORT
            && enqueue->port != OFPP_LOCAL) {
            return OFPERR_OFPBAC_BAD_OUT_PORT;
        }
        return 0;

    case OFPACT_OUTPUT_REG:
        return mf_check_src(&ofpact_get_OUTPUT_REG(a)->src, flow);

    case OFPACT_OUTPUT_TRUNC:
        return ofpact_check_output_port(ofpact_get_OUTPUT_TRUNC(a)->port,
                                        max_ports);

    case OFPACT_BUNDLE:
        return bundle_check(ofpact_get_BUNDLE(a), max_ports, flow);

    case OFPACT_SET_VLAN_VID:
        /* Remember if we saw a vlan tag in the flow to aid translating to
         * OpenFlow 1.1+ if need be. */
        ofpact_get_SET_VLAN_VID(a)->flow_has_vlan =
            (flow->vlan_tci & htons(VLAN_CFI)) == htons(VLAN_CFI);
        if (!(flow->vlan_tci & htons(VLAN_CFI)) &&
            !ofpact_get_SET_VLAN_VID(a)->push_vlan_if_needed) {
            inconsistent_match(usable_protocols);
        }
        /* Temporary mark that we have a vlan tag. */
        flow->vlan_tci |= htons(VLAN_CFI);
        return 0;

    case OFPACT_SET_VLAN_PCP:
        /* Remember if we saw a vlan tag in the flow to aid translating to
         * OpenFlow 1.1+ if need be. */
        ofpact_get_SET_VLAN_PCP(a)->flow_has_vlan =
            (flow->vlan_tci & htons(VLAN_CFI)) == htons(VLAN_CFI);
        if (!(flow->vlan_tci & htons(VLAN_CFI)) &&
            !ofpact_get_SET_VLAN_PCP(a)->push_vlan_if_needed) {
            inconsistent_match(usable_protocols);
        }
        /* Temporary mark that we have a vlan tag. */
        flow->vlan_tci |= htons(VLAN_CFI);
        return 0;

    case OFPACT_STRIP_VLAN:
        if (!(flow->vlan_tci & htons(VLAN_CFI))) {
            inconsistent_match(usable_protocols);
        }
        /* Temporary mark that we have no vlan tag. */
        flow->vlan_tci = htons(0);
        return 0;

    case OFPACT_PUSH_VLAN:
        if (flow->vlan_tci & htons(VLAN_CFI)) {
            /* Multiple VLAN headers not supported. */
            return OFPERR_OFPBAC_BAD_TAG;
        }
        /* Temporary mark that we have a vlan tag. */
        flow->vlan_tci |= htons(VLAN_CFI);
        return 0;

    case OFPACT_SET_ETH_SRC:
    case OFPACT_SET_ETH_DST:
        return 0;

    case OFPACT_SET_IPV4_SRC:
    case OFPACT_SET_IPV4_DST:
        if (flow->dl_type != htons(ETH_TYPE_IP)) {
            inconsistent_match(usable_protocols);
        }
        return 0;

    case OFPACT_SET_IP_DSCP:
    case OFPACT_SET_IP_ECN:
    case OFPACT_SET_IP_TTL:
    case OFPACT_DEC_TTL:
        if (!is_ip_any(flow)) {
            inconsistent_match(usable_protocols);
        }
        return 0;

    case OFPACT_SET_L4_SRC_PORT:
    case OFPACT_SET_L4_DST_PORT:
        if (!is_ip_any(flow) || (flow->nw_frag & FLOW_NW_FRAG_LATER) ||
            (flow->nw_proto != IPPROTO_TCP && flow->nw_proto != IPPROTO_UDP
             && flow->nw_proto != IPPROTO_SCTP)) {
            inconsistent_match(usable_protocols);
        }
        /* Note on which transport protocol the port numbers are set.
         * This allows this set action to be converted to an OF1.2 set field
         * action. */
        if (a->type == OFPACT_SET_L4_SRC_PORT) {
            ofpact_get_SET_L4_SRC_PORT(a)->flow_ip_proto = flow->nw_proto;
        } else {
            ofpact_get_SET_L4_DST_PORT(a)->flow_ip_proto = flow->nw_proto;
        }
        return 0;

    case OFPACT_REG_MOVE:
        return nxm_reg_move_check(ofpact_get_REG_MOVE(a), flow);

    case OFPACT_SET_FIELD:
        mf = ofpact_get_SET_FIELD(a)->field;
        /* Require OXM_OF_VLAN_VID to have an existing VLAN header. */
        if (!mf_are_prereqs_ok(mf, flow, NULL) ||
            (mf->id == MFF_VLAN_VID && !(flow->vlan_tci & htons(VLAN_CFI)))) {
            VLOG_WARN_RL(&rl, "set_field %s lacks correct prerequisities",
                         mf->name);
            return OFPERR_OFPBAC_MATCH_INCONSISTENT;
        }
        /* Remember if we saw a vlan tag in the flow to aid translating to
         * OpenFlow 1.1 if need be. */
        ofpact_get_SET_FIELD(a)->flow_has_vlan =
            (flow->vlan_tci & htons(VLAN_CFI)) == htons(VLAN_CFI);
        if (mf->id == MFF_VLAN_TCI) {
            /* The set field may add or remove the vlan tag,
             * Mark the status temporarily. */
            flow->vlan_tci = ofpact_get_SET_FIELD(a)->value->be16;
        }
        return 0;

    case OFPACT_STACK_PUSH:
        return nxm_stack_push_check(ofpact_get_STACK_PUSH(a), flow);

    case OFPACT_STACK_POP:
        return nxm_stack_pop_check(ofpact_get_STACK_POP(a), flow);

    case OFPACT_SET_MPLS_LABEL:
    case OFPACT_SET_MPLS_TC:
    case OFPACT_SET_MPLS_TTL:
    case OFPACT_DEC_MPLS_TTL:
        if (!eth_type_mpls(flow->dl_type)) {
            inconsistent_match(usable_protocols);
        }
        return 0;

    case OFPACT_SET_TUNNEL:
    case OFPACT_SET_QUEUE:
    case OFPACT_POP_QUEUE:
    case OFPACT_RESUBMIT:
        return 0;

    case OFPACT_FIN_TIMEOUT:
        if (flow->nw_proto != IPPROTO_TCP) {
            inconsistent_match(usable_protocols);
        }
        return 0;

    case OFPACT_LEARN:
        return learn_check(ofpact_get_LEARN(a), flow);

    case OFPACT_CONJUNCTION:
        return 0;

    case OFPACT_MULTIPATH:
        return multipath_check(ofpact_get_MULTIPATH(a), flow);

    case OFPACT_NOTE:
    case OFPACT_EXIT:
        return 0;

    case OFPACT_PUSH_MPLS:
        flow->dl_type = ofpact_get_PUSH_MPLS(a)->ethertype;
        /* The packet is now MPLS and the MPLS payload is opaque.
         * Thus nothing can be assumed about the network protocol.
         * Temporarily mark that we have no nw_proto. */
        flow->nw_proto = 0;
        return 0;

    case OFPACT_POP_MPLS:
        if (!eth_type_mpls(flow->dl_type)) {
            inconsistent_match(usable_protocols);
        }
        flow->dl_type = ofpact_get_POP_MPLS(a)->ethertype;
        return 0;

    case OFPACT_SAMPLE:
        return 0;

    case OFPACT_CLONE: {
        struct ofpact_nest *on = ofpact_get_CLONE(a);
        return ofpacts_check(on->actions, ofpact_nest_get_action_len(on),
                             flow, max_ports, table_id, n_tables,
                             usable_protocols);
    }

    case OFPACT_CT: {
        struct ofpact_conntrack *oc = ofpact_get_CT(a);

        if (!dl_type_is_ip_any(flow->dl_type)
            || (flow->ct_state & CS_INVALID && oc->flags & NX_CT_F_COMMIT)
            || (oc->alg == IPPORT_FTP && flow->nw_proto != IPPROTO_TCP)
            || (oc->alg == IPPORT_TFTP && flow->nw_proto != IPPROTO_UDP)) {
            /* We can't downgrade to OF1.0 and expect inconsistent CT actions
             * be silently discarded.  Instead, datapath flow install fails, so
             * it is better to flag inconsistent CT actions as hard errors. */
            return OFPERR_OFPBAC_MATCH_INCONSISTENT;
        }

        if (oc->zone_src.field) {
            return mf_check_src(&oc->zone_src, flow);
        }

        return ofpacts_check(oc->actions, ofpact_ct_get_action_len(oc),
                             flow, max_ports, table_id, n_tables,
                             usable_protocols);
    }

    case OFPACT_CT_CLEAR:
        return 0;

    case OFPACT_NAT: {
        struct ofpact_nat *on = ofpact_get_NAT(a);

        if (!dl_type_is_ip_any(flow->dl_type) ||
            (on->range_af == AF_INET && flow->dl_type != htons(ETH_TYPE_IP)) ||
            (on->range_af == AF_INET6
             && flow->dl_type != htons(ETH_TYPE_IPV6))) {
            return OFPERR_OFPBAC_MATCH_INCONSISTENT;
        }
        return 0;
    }

    case OFPACT_CLEAR_ACTIONS:
        return 0;

    case OFPACT_WRITE_ACTIONS: {
        /* Use a temporary copy of 'usable_protocols' because we can't check
         * consistency of an action set. */
        struct ofpact_nest *on = ofpact_get_WRITE_ACTIONS(a);
        enum ofputil_protocol p = *usable_protocols;
        return ofpacts_check(on->actions, ofpact_nest_get_action_len(on),
                             flow, max_ports, table_id, n_tables, &p);
    }

    case OFPACT_WRITE_METADATA:
        return 0;

    case OFPACT_METER: {
        uint32_t mid = ofpact_get_METER(a)->meter_id;
        if (mid == 0 || mid > OFPM13_MAX) {
            return OFPERR_OFPMMFC_INVALID_METER;
        }
        return 0;
    }

    case OFPACT_GOTO_TABLE: {
        uint8_t goto_table = ofpact_get_GOTO_TABLE(a)->table_id;
        if ((table_id != 255 && goto_table <= table_id)
            || (n_tables != 255 && goto_table >= n_tables)) {
            return OFPERR_OFPBIC_BAD_TABLE_ID;
        }
        return 0;
    }

    case OFPACT_GROUP:
        return 0;

    case OFPACT_UNROLL_XLATE:
        /* UNROLL is an internal action that should never be seen via
         * OpenFlow. */
        return OFPERR_OFPBAC_BAD_TYPE;

    case OFPACT_DEBUG_RECIRC:
        return 0;

    default:
        OVS_NOT_REACHED();
    }
}
