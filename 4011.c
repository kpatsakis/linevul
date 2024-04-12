static int hadamard8_intra8x8_c(/*MpegEncContext*/ void *s, uint8_t *src, uint8_t *dummy, int stride, int h){
    int i;
    int temp[64];
    int sum=0;

    av_assert2(h==8);

    for(i=0; i<8; i++){
        BUTTERFLY2(temp[8*i+0], temp[8*i+1], src[stride*i+0],src[stride*i+1]);
        BUTTERFLY2(temp[8*i+2], temp[8*i+3], src[stride*i+2],src[stride*i+3]);
        BUTTERFLY2(temp[8*i+4], temp[8*i+5], src[stride*i+4],src[stride*i+5]);
        BUTTERFLY2(temp[8*i+6], temp[8*i+7], src[stride*i+6],src[stride*i+7]);

        BUTTERFLY1(temp[8*i+0], temp[8*i+2]);
        BUTTERFLY1(temp[8*i+1], temp[8*i+3]);
        BUTTERFLY1(temp[8*i+4], temp[8*i+6]);
        BUTTERFLY1(temp[8*i+5], temp[8*i+7]);

        BUTTERFLY1(temp[8*i+0], temp[8*i+4]);
        BUTTERFLY1(temp[8*i+1], temp[8*i+5]);
        BUTTERFLY1(temp[8*i+2], temp[8*i+6]);
        BUTTERFLY1(temp[8*i+3], temp[8*i+7]);
    }

    for(i=0; i<8; i++){
        BUTTERFLY1(temp[8*0+i], temp[8*1+i]);
        BUTTERFLY1(temp[8*2+i], temp[8*3+i]);
        BUTTERFLY1(temp[8*4+i], temp[8*5+i]);
        BUTTERFLY1(temp[8*6+i], temp[8*7+i]);

        BUTTERFLY1(temp[8*0+i], temp[8*2+i]);
        BUTTERFLY1(temp[8*1+i], temp[8*3+i]);
        BUTTERFLY1(temp[8*4+i], temp[8*6+i]);
        BUTTERFLY1(temp[8*5+i], temp[8*7+i]);

        sum +=
             BUTTERFLYA(temp[8*0+i], temp[8*4+i])
            +BUTTERFLYA(temp[8*1+i], temp[8*5+i])
            +BUTTERFLYA(temp[8*2+i], temp[8*6+i])
            +BUTTERFLYA(temp[8*3+i], temp[8*7+i]);
    }

    sum -= FFABS(temp[8*0] + temp[8*4]); // -mean

    return sum;
}
