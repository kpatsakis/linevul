  event_bold_change( double  delta )
  {
    status.bold_factor += delta;

    if ( status.bold_factor > 0.1 )
      status.bold_factor = 0.1;
    else if ( status.bold_factor < -0.1 )
      status.bold_factor = -0.1;

    sprintf( status.header_buffer, "embolding factor changed to %.3f",
             status.bold_factor );

    status.header = status.header_buffer;
  }
