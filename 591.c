static rfc_slot_t *find_rfc_slot_by_pending_sdp(void) {
 uint32_t min_id = UINT32_MAX;
 int slot = -1;
 for (size_t i = 0; i < ARRAY_SIZE(rfc_slots); ++i)
 if (rfc_slots[i].id && rfc_slots[i].f.pending_sdp_request && rfc_slots[i].id < min_id) {
      min_id = rfc_slots[i].id;
      slot = i;
 }

 return (slot == -1) ? NULL : &rfc_slots[slot];
}
