  FT_New_Face( FT_Library   library,
               const char*  pathname,
               FT_Long      face_index,
               FT_Face     *aface )
  {
    FT_Open_Args  args;


    /* test for valid `library' and `aface' delayed to FT_Open_Face() */
    if ( !pathname )
      return FT_Err_Invalid_Argument;

    args.flags    = FT_OPEN_PATHNAME;
    args.pathname = (char*)pathname;
    args.stream   = NULL;

    return FT_Open_Face( library, &args, face_index, aface );
  }
