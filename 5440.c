  FT_Stream_New( FT_Library           library,
                 const FT_Open_Args*  args,
                 FT_Stream           *astream )
  {
    FT_Error   error;
    FT_Memory  memory;
    FT_Stream  stream = NULL;


    *astream = 0;

    if ( !library )
      return FT_THROW( Invalid_Library_Handle );

    if ( !args )
      return FT_THROW( Invalid_Argument );

    memory = library->memory;

    if ( FT_NEW( stream ) )
      goto Exit;

    stream->memory = memory;

    if ( args->flags & FT_OPEN_MEMORY )
    {
      /* create a memory-based stream */
      FT_Stream_OpenMemory( stream,
                            (const FT_Byte*)args->memory_base,
                            args->memory_size );
    }

#ifndef FT_CONFIG_OPTION_DISABLE_STREAM_SUPPORT

    else if ( args->flags & FT_OPEN_PATHNAME )
    {
      /* create a normal system stream */
      error = FT_Stream_Open( stream, args->pathname );
      stream->pathname.pointer = args->pathname;
    }
    else if ( ( args->flags & FT_OPEN_STREAM ) && args->stream )
    {
      /* use an existing, user-provided stream */

      /* in this case, we do not need to allocate a new stream object */
      /* since the caller is responsible for closing it himself       */
      FT_FREE( stream );
      stream = args->stream;
    }

#endif

    else
      error = FT_THROW( Invalid_Argument );

    if ( error )
      FT_FREE( stream );
    else
      stream->memory = memory;  /* just to be certain */

    *astream = stream;

  Exit:
    return error;
  }
