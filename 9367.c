OSCL_EXPORT_REF Bool PVCleanUpVideoDecoder(VideoDecControls *decCtrl)
{
 int idx;
 VideoDecData *video = (VideoDecData *) decCtrl->videoDecoderData;
#ifdef DEC_INTERNAL_MEMORY_OPT
 if (video)
 {
#ifdef PV_POSTPROC_ON
        video->pstprcTypCur = NULL;
        video->pstprcTypPrv = NULL;
#endif

        video->acPredFlag       = NULL;
        video->sliceNo          = NULL;
        video->motX             = NULL;
        video->motY             = NULL;
        video->mblock           = NULL;
        video->QPMB             = NULL;
        video->predDC           = NULL;
        video->predDCAC_row     = NULL;
        video->predDCAC_col     = NULL;
        video->headerInfo.Mode = NULL;
        video->headerInfo.CBP   = NULL;
 if (video->numberOfLayers > 1)
 {
 if (video->prevEnhcVop)
 {
                video->prevEnhcVop->uChan = NULL;
                video->prevEnhcVop->vChan = NULL;
 if (video->prevEnhcVop->yChan) oscl_free(video->prevEnhcVop->yChan);
                oscl_free(video->prevEnhcVop);
 }
 }
 if (video->currVop)
 {
            video->currVop->uChan = NULL;
            video->currVop->vChan = NULL;
 if (video->currVop->yChan)
                video->currVop->yChan = NULL;
            video->currVop = NULL;
 }
 if (video->prevVop)
 {
            video->prevVop->uChan = NULL;
            video->prevVop->vChan = NULL;
 if (video->prevVop->yChan)
                video->prevVop->yChan = NULL;
            video->prevVop = NULL;
 }

 if (video->vol)
 {
 for (idx = 0; idx < video->numberOfLayers; idx++)
 {
 if (video->vol[idx])
 {
 BitstreamClose(video->vol[idx]->bitstream);
                    video->vol[idx]->bitstream = NULL;
                    video->vol[idx] = NULL;
 }
                video->vopHeader[idx] = NULL;

 }
            video->vol = NULL;
            video->vopHeader = NULL;
 }

        video = NULL;
        decCtrl->videoDecoderData = NULL;
 }

#else

 if (video)
 {
#ifdef PV_POSTPROC_ON
 if (video->pstprcTypCur) oscl_free(video->pstprcTypCur);
 if (video->pstprcTypPrv) oscl_free(video->pstprcTypPrv);
#endif
 if (video->predDC) oscl_free(video->predDC);
        video->predDCAC_row = NULL;
 if (video->predDCAC_col) oscl_free(video->predDCAC_col);
 if (video->motX) oscl_free(video->motX);
 if (video->motY) oscl_free(video->motY);
 if (video->mblock) oscl_free(video->mblock);
 if (video->QPMB) oscl_free(video->QPMB);
 if (video->headerInfo.Mode) oscl_free(video->headerInfo.Mode);
 if (video->headerInfo.CBP) oscl_free(video->headerInfo.CBP);
 if (video->sliceNo) oscl_free(video->sliceNo);
 if (video->acPredFlag) oscl_free(video->acPredFlag);

 if (video->numberOfLayers > 1)
 {
 if (video->prevEnhcVop)
 {
                video->prevEnhcVop->uChan = NULL;
                video->prevEnhcVop->vChan = NULL;
 if (video->prevEnhcVop->yChan) oscl_free(video->prevEnhcVop->yChan);
                oscl_free(video->prevEnhcVop);
 }
 }
 if (video->currVop)
 {

#ifndef PV_MEMORY_POOL
            video->currVop->uChan = NULL;
            video->currVop->vChan = NULL;
 if (video->currVop->yChan)
                oscl_free(video->currVop->yChan);
#endif
            oscl_free(video->currVop);
 }
 if (video->prevVop)
 {
#ifndef PV_MEMORY_POOL
            video->prevVop->uChan = NULL;
            video->prevVop->vChan = NULL;
 if (video->prevVop->yChan)
                oscl_free(video->prevVop->yChan);
#endif
            oscl_free(video->prevVop);
 }

 if (video->vol)
 {
 for (idx = 0; idx < video->numberOfLayers; idx++)
 {
 if (video->vol[idx])
 {
 if (video->vol[idx]->bitstream)
 {
 BitstreamClose(video->vol[idx]->bitstream);
                        oscl_free(video->vol[idx]->bitstream);
 }
                    oscl_free(video->vol[idx]);
 }

 }
            oscl_free(video->vol);
 }

 for (idx = 0; idx < video->numberOfLayers; idx++)
 {
 if (video->vopHeader[idx]) oscl_free(video->vopHeader[idx]);
 }

 if (video->vopHeader) oscl_free(video->vopHeader);

        oscl_free(video);
        decCtrl->videoDecoderData = NULL;
 }
#endif
 return PV_TRUE;
}
