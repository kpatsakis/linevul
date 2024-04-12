decode_legacy_async_masks(const ovs_be32 masks[2],
                          enum ofputil_async_msg_type oam,
                          enum ofp_version version,
                          struct ofputil_async_cfg *dst)
{
    for (int i = 0; i < 2; i++) {
        bool master = i == 0;
        const struct ofp14_async_prop *ap
            = get_ofp14_async_config_prop_by_oam(oam, master);
        decode_async_mask(masks[i], ap, version, true, dst);
    }
}
