  Render_All( int  num_indices,
              int  first_index )
  {
    int      start_x, start_y, step_x, step_y, x, y;
    int      i;
    FT_Size  size;


    error = FTDemo_Get_Size( handle, &size );

    if ( error )
    {
      /* probably a non-existent bitmap font size */
      return error;
    }

    INIT_SIZE( size, start_x, start_y, step_x, step_y, x, y );

    i = first_index;

    while ( i < num_indices )
    {
      int  gindex;


      if ( handle->encoding == FT_ENCODING_NONE )
        gindex = i;
      else
        gindex = FTDemo_Get_Index( handle, i );

      error = FTDemo_Draw_Index( handle, display, gindex, &x, &y );
      if ( error )
        status.Fail++;
      else if ( X_TOO_LONG( x, size, display ) )
      {
        x = start_x;
        y += step_y;

        if ( Y_TOO_LONG( y, size, display ) )
          break;
      }

      i++;
    }

    return FT_Err_Ok;
  }
