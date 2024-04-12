static bool is_requesting_sdp(void) {
 for (size_t i = 0; i < ARRAY_SIZE(rfc_slots); ++i)
 if (rfc_slots[i].id && rfc_slots[i].f.doing_sdp_request)
 return true;
 return false;
}
