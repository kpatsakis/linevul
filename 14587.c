  cf2_glyphpath_hintPoint( CF2_GlyphPath  glyphpath,
                           CF2_HintMap    hintmap,
                           FT_Vector*     ppt,
                           CF2_Fixed      x,
                           CF2_Fixed      y )
  {
    FT_Vector  pt;   /* hinted point in upright DS */


    pt.x = FT_MulFix( glyphpath->scaleX, x ) +
             FT_MulFix( glyphpath->scaleC, y );
    pt.y = cf2_hintmap_map( hintmap, y );

    ppt->x = FT_MulFix( glyphpath->font->outerTransform.a, pt.x )   +
               FT_MulFix( glyphpath->font->outerTransform.c, pt.y ) +
               glyphpath->fractionalTranslation.x;
    ppt->y = FT_MulFix( glyphpath->font->outerTransform.b, pt.x )   +
               FT_MulFix( glyphpath->font->outerTransform.d, pt.y ) +
               glyphpath->fractionalTranslation.y;
  }
