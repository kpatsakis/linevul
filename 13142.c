  Ins_MDAP( TT_ExecContext  exc,
            FT_Long*        args )
  {
    FT_UShort   point;
    FT_F26Dot6  cur_dist;
    FT_F26Dot6  distance;


    point = (FT_UShort)args[0];

    if ( BOUNDS( point, exc->zp0.n_points ) )
    {
      if ( exc->pedantic_hinting )
        exc->error = FT_THROW( Invalid_Reference );
      return;
    }

    if ( ( exc->opcode & 1 ) != 0 )
    {
      cur_dist = FAST_PROJECT( &exc->zp0.cur[point] );
#ifdef TT_SUPPORT_SUBPIXEL_HINTING_INFINALITY
      if ( SUBPIXEL_HINTING_INFINALITY &&
           exc->ignore_x_mode          &&
           exc->GS.freeVector.x != 0   )
        distance = Round_None(
                     exc,
                     cur_dist,
                     exc->tt_metrics.compensations[0] ) - cur_dist;
      else
#endif
        distance = exc->func_round(
                     exc,
                     cur_dist,
                     exc->tt_metrics.compensations[0] ) - cur_dist;
    }
    else
      distance = 0;

    exc->func_move( exc, &exc->zp0, point, distance );

    exc->GS.rp0 = point;
    exc->GS.rp1 = point;
  }
