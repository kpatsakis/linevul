WORD32 ihevcd_get_lvl_idx(WORD32 level)
{
    WORD32 lvl_idx = 0;

 if(level < IHEVC_LEVEL_20)
 {
        lvl_idx = 0;
 }
 else if(level >= IHEVC_LEVEL_20 && level < IHEVC_LEVEL_21)
 {
        lvl_idx = 1;
 }
 else if(level >= IHEVC_LEVEL_21 && level < IHEVC_LEVEL_30)
 {
        lvl_idx = 2;
 }
 else if(level >= IHEVC_LEVEL_30 && level < IHEVC_LEVEL_31)
 {
        lvl_idx = 3;
 }
 else if(level >= IHEVC_LEVEL_31 && level < IHEVC_LEVEL_40)
 {
        lvl_idx = 4;
 }
 else if(level >= IHEVC_LEVEL_40 && level < IHEVC_LEVEL_41)
 {
        lvl_idx = 5;
 }
 else if(level >= IHEVC_LEVEL_41 && level < IHEVC_LEVEL_50)
 {
        lvl_idx = 6;
 }
 else if(level >= IHEVC_LEVEL_50 && level < IHEVC_LEVEL_51)
 {
        lvl_idx = 7;
 }
 else if(level >= IHEVC_LEVEL_51 && level < IHEVC_LEVEL_52)
 {
        lvl_idx = 8;
 }
 else if(level >= IHEVC_LEVEL_52 && level < IHEVC_LEVEL_60)
 {
        lvl_idx = 9;
 }
 else if(level >= IHEVC_LEVEL_60 && level < IHEVC_LEVEL_61)
 {
        lvl_idx = 10;
 }
 else if(level >= IHEVC_LEVEL_61 && level < IHEVC_LEVEL_62)
 {
        lvl_idx = 11;
 }
 else if(level >= IHEVC_LEVEL_62)
 {
        lvl_idx = 12;
 }

 return (lvl_idx);
}
