grid_status_draw_grid( GridStatus  st )
{
  int     x_org   = (int)st->x_origin;
  int     y_org   = (int)st->y_origin;
  double  xy_incr = 64.0 * st->scale;

  if ( xy_incr >= 2. )
  {
    double  x2 = x_org;
    double  y2 = y_org;

    for ( ; x2 < st->disp_width; x2 += xy_incr )
      grFillVLine( st->disp_bitmap, (int)x2, 0,
                   st->disp_height, st->grid_color );

    for ( x2 = x_org - xy_incr; (int)x2 >= 0; x2 -= xy_incr )
      grFillVLine( st->disp_bitmap, (int)x2, 0,
                   st->disp_height, st->grid_color );

    for ( ; y2 < st->disp_height; y2 += xy_incr )
      grFillHLine( st->disp_bitmap, 0, (int)y2,
                   st->disp_width, st->grid_color );

    for ( y2 = y_org - xy_incr; (int)y2 >= 0; y2 -= xy_incr )
      grFillHLine( st->disp_bitmap, 0, (int)y2,
                   st->disp_width, st->grid_color );
  }

  grFillVLine( st->disp_bitmap, x_org, 0, st->disp_height, st->axis_color );
  grFillHLine( st->disp_bitmap, 0, y_org, st->disp_width,  st->axis_color );
}
