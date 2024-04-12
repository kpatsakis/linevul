void BTM_SetPairableMode (BOOLEAN allow_pairing, BOOLEAN connect_only_paired)
{
    BTM_TRACE_API ("BTM_SetPairableMode()  allow_pairing: %u   connect_only_paired: %u", allow_pairing, connect_only_paired);

    btm_cb.pairing_disabled    = !allow_pairing;
    btm_cb.connect_only_paired = connect_only_paired;
}
