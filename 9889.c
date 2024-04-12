gx_dc_pattern_read_trans_buff(gx_color_tile *ptile, int64_t offset,
                              const byte *data, uint size, gs_memory_t *mem)
{
    const byte *dp = data;
    int left = size;
    int64_t offset1 = offset;
    gx_pattern_trans_t *trans_pat = ptile->ttrans;
    int data_size;

    data_size = trans_pat->planestride * trans_pat->n_chan;
    if (trans_pat->has_tags)
        data_size += trans_pat->planestride;

    /* Allocate the bytes */
    if (trans_pat->transbytes == NULL){
        trans_pat->transbytes = gs_alloc_bytes(mem, data_size, "gx_dc_pattern_read_raster");
        trans_pat->mem = mem;
        if (trans_pat->transbytes == NULL)
                return_error(gs_error_VMerror);
    }
    /* Read transparency buffer */
    if (offset1 <= sizeof(gx_dc_serialized_tile_t) + sizeof(tile_trans_clist_info_t) + data_size ) {

        int u = min(data_size, left);
        byte *save = trans_pat->transbytes;

        memcpy( trans_pat->transbytes + offset1 - sizeof(gx_dc_serialized_tile_t) -
                                    sizeof(tile_trans_clist_info_t), dp, u);
        trans_pat->transbytes = save;
        left -= u;
    }
     return size - left;
}
