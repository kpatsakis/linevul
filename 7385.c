  cf2_glyphpath_moveTo( CF2_GlyphPath  glyphpath,
                        CF2_Fixed      x,
                        CF2_Fixed      y )
  {
    cf2_glyphpath_closeOpenPath( glyphpath );

    /* save the parameters of the move for later, when we'll know how to */
    /* offset it;                                                        */
    /* also save last move point */
    glyphpath->currentCS.x = glyphpath->start.x = x;
    glyphpath->currentCS.y = glyphpath->start.y = y;

    glyphpath->moveIsPending = TRUE;

    /* ensure we have a valid map with current mask */
    if ( !cf2_hintmap_isValid( &glyphpath->hintMap ) ||
         cf2_hintmask_isNew( glyphpath->hintMask )   )
      cf2_hintmap_build( &glyphpath->hintMap,
                         glyphpath->hStemHintArray,
                         glyphpath->vStemHintArray,
                         glyphpath->hintMask,
                         glyphpath->hintOriginY,
                         FALSE );

    /* save a copy of current HintMap to use when drawing initial point */
    glyphpath->firstHintMap = glyphpath->hintMap;     /* structure copy */
  }
