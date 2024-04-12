  destroy_size( FT_Memory  memory,
                FT_Size    size,
                FT_Driver  driver )
  {
    /* finalize client-specific data */
    if ( size->generic.finalizer )
      size->generic.finalizer( size );

    /* finalize format-specific stuff */
    if ( driver->clazz->done_size )
      driver->clazz->done_size( size );

    FT_FREE( size->internal );
    FT_FREE( size );
  }
