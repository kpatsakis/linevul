void ff_set_cmp(DSPContext* c, me_cmp_func *cmp, int type){
    int i;

    memset(cmp, 0, sizeof(void*)*6);

    for(i=0; i<6; i++){
        switch(type&0xFF){
        case FF_CMP_SAD:
            cmp[i]= c->sad[i];
            break;
        case FF_CMP_SATD:
            cmp[i]= c->hadamard8_diff[i];
            break;
        case FF_CMP_SSE:
            cmp[i]= c->sse[i];
            break;
        case FF_CMP_DCT:
            cmp[i]= c->dct_sad[i];
            break;
        case FF_CMP_DCT264:
            cmp[i]= c->dct264_sad[i];
            break;
        case FF_CMP_DCTMAX:
            cmp[i]= c->dct_max[i];
            break;
        case FF_CMP_PSNR:
            cmp[i]= c->quant_psnr[i];
            break;
        case FF_CMP_BIT:
            cmp[i]= c->bit[i];
            break;
        case FF_CMP_RD:
            cmp[i]= c->rd[i];
            break;
        case FF_CMP_VSAD:
            cmp[i]= c->vsad[i];
            break;
        case FF_CMP_VSSE:
            cmp[i]= c->vsse[i];
            break;
        case FF_CMP_ZERO:
            cmp[i]= zero_cmp;
            break;
        case FF_CMP_NSSE:
            cmp[i]= c->nsse[i];
            break;
#if CONFIG_DWT
        case FF_CMP_W53:
            cmp[i]= c->w53[i];
            break;
        case FF_CMP_W97:
            cmp[i]= c->w97[i];
            break;
#endif
        default:
            av_log(NULL, AV_LOG_ERROR,"internal error in cmp function selection\n");
        }
    }
}
