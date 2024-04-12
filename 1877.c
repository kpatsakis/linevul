static int vsse16_c(/*MpegEncContext*/ void *c, uint8_t *s1, uint8_t *s2, int stride, int h){
    int score=0;
    int x,y;

    for(y=1; y<h; y++){
        for(x=0; x<16; x++){
            score+= SQ(s1[x  ] - s2[x ] - s1[x  +stride] + s2[x +stride]);
        }
        s1+= stride;
        s2+= stride;
    }

    return score;
}
