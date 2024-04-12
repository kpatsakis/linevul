int res_inverse(vorbis_dsp_state *vd,vorbis_info_residue *info,
 ogg_int32_t **in,int *nonzero,int ch){

 int i,j,k,s,used=0;
  codec_setup_info     *ci=(codec_setup_info *)vd->vi->codec_setup;
  codebook *phrasebook=ci->book_param+info->groupbook;
 int samples_per_partition=info->grouping;
 int partitions_per_word=phrasebook->dim;
 int pcmend=ci->blocksizes[vd->W];

 if(info->type<2){
 int max=pcmend>>1;
 int end=(info->end<max?info->end:max);
 int n=end-info->begin;

 if(n>0){
 int partvals=n/samples_per_partition;
 int partwords=(partvals+partitions_per_word-1)/partitions_per_word;

 for(i=0;i<ch;i++)
 if(nonzero[i])
          in[used++]=in[i];
      ch=used;

 if(used){

 char **partword=(char **)_ogg_calloc(ch,sizeof(*partword));
 if(partword==NULL)goto cleanup1;
 for(j=0;j<ch;j++){
          partword[j]=(char *)_ogg_malloc(partwords*partitions_per_word*
 sizeof(*partword[j]));
 if(partword[j]==NULL)goto cleanup1;
 }

 for(s=0;s<info->stages;s++){

 for(i=0;i<partvals;){
 if(s==0){
 /* fetch the partition word for each channel */

              partword[0][i+partitions_per_word-1]=1;
 for(k=partitions_per_word-2;k>=0;k--)
                partword[0][i+k]=partword[0][i+k+1]*info->partitions;

 for(j=1;j<ch;j++)
 for(k=partitions_per_word-1;k>=0;k--)
                  partword[j][i+k]=partword[j-1][i+k];

 for(j=0;j<ch;j++){
 int temp=vorbis_book_decode(phrasebook,&vd->opb);
 if(temp==-1)goto cleanup1;

 /* this can be done quickly in assembly due to the quotient
                   always being at most six bits */
 for(k=0;k<partitions_per_word;k++){
 ogg_uint32_t div=partword[j][i+k];
                  partword[j][i+k]= (div == 0) ? 0 : (temp / div);
                  temp-=partword[j][i+k]*div;
 }

 }
 }

 /* now we decode residual values for the partitions */
 for(k=0;k<partitions_per_word && i<partvals;k++,i++)
 for(j=0;j<ch;j++){
 long offset=info->begin+i*samples_per_partition;
 int idx = (int)partword[j][i];
 if(idx < info->partitions && info->stagemasks[idx]&(1<<s)){
                  codebook *stagebook=ci->book_param+
                    info->stagebooks[(partword[j][i]<<3)+s];
 if(info->type){
 if(vorbis_book_decodev_add(stagebook,in[j]+offset,&vd->opb,
                                               samples_per_partition,-8)==-1)
 goto cleanup1;
 }else{
 if(vorbis_book_decodevs_add(stagebook,in[j]+offset,&vd->opb,
                                                samples_per_partition,-8)==-1)
 goto cleanup1;
 }
 }
 }
 }
 }
 cleanup1:
 if(partword){
 for(j=0;j<ch;j++){
 if(partword[j])_ogg_free(partword[j]);
 }
          _ogg_free(partword);
 }
 }
 }
 }else{
 int max=(pcmend*ch)>>1;
 int end=(info->end<max?info->end:max);
 int n=end-info->begin;

 if(n>0){
 int partvals=n/samples_per_partition;
 int partwords=(partvals+partitions_per_word-1)/partitions_per_word;

 char *partword=
 (char *)_ogg_malloc(partwords*partitions_per_word*sizeof(*partword));
 if(partword==NULL)goto cleanup2;
 int beginoff=info->begin/ch;

 for(i=0;i<ch;i++)if(nonzero[i])break;
 if(i==ch)goto cleanup2; /* no nonzero vectors */

      samples_per_partition/=ch;

 for(s=0;s<info->stages;s++){
 for(i=0;i<partvals;){

 if(s==0){
 int temp;
            partword[i+partitions_per_word-1]=1;
 for(k=partitions_per_word-2;k>=0;k--)
              partword[i+k]=partword[i+k+1]*info->partitions;

 /* fetch the partition word */
            temp=vorbis_book_decode(phrasebook,&vd->opb);
 if(temp==-1)goto cleanup2;

 /* this can be done quickly in assembly due to the quotient
               always being at most six bits */
 for(k=0;k<partitions_per_word;k++){
 ogg_uint32_t div=partword[i+k];
              partword[i+k]= (div == 0) ? 0 : (temp / div);
              temp-=partword[i+k]*div;
 }
 }

 /* now we decode residual values for the partitions */
 for(k=0;k<partitions_per_word && i<partvals;k++,i++){
 if(partword[i] >= 0 && partword[i] < info->partitions &&
 (info->stagemasks[(int)partword[i]] & (1 << s))){
                  codebook *stagebook=ci->book_param+
                          info->stagebooks[(partword[i]<<3)+s];
 if(vorbis_book_decodevv_add(stagebook,in,
                              i*samples_per_partition+beginoff,ch,
 &vd->opb,
                              samples_per_partition,-8)==-1)
 goto cleanup2;
 }
 }
 }
 }
 cleanup2:
 if(partword)_ogg_free(partword);
 }
 }

 return 0;
}
