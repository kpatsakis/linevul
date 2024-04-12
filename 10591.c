  Help( void )
  {
    grEvent  dummy_event;


    Clear_Display();

    grGotoxy( 0, 0 );
    grSetMargin( 2, 1 );
    grGotobitmap( &bit );

    grWriteln( "FreeType Multiple Masters Glyph Viewer - part of the FreeType test suite" );
    grLn();
    grWriteln( "This program is used to display all glyphs from one or" );
    grWriteln( "several Multiple Masters font files, with the FreeType library.");
    grLn();
    grWriteln( "Use the following keys:");
    grLn();
    grWriteln( "  F1 or ?   : display this help screen" );
    grWriteln( "  a         : toggle anti-aliasing" );
    grWriteln( "  h         : toggle outline hinting" );
    grWriteln( "  b         : toggle embedded bitmaps" );
    grWriteln( "  l         : toggle low precision rendering" );
    grWriteln( "  space     : toggle rendering mode" );
    grLn();
    grWriteln( "  n         : next font" );
    grWriteln( "  p         : previous font" );
    grLn();
    grWriteln( "  Up        : increase pointsize by 1 unit" );
    grWriteln( "  Down      : decrease pointsize by 1 unit" );
    grWriteln( "  Page Up   : increase pointsize by 10 units" );
    grWriteln( "  Page Down : decrease pointsize by 10 units" );
    grLn();
    grWriteln( "  Right     : increment first glyph index" );
    grWriteln( "  Left      : decrement first glyph index" );
    grLn();
    grWriteln( "  F3        : decrement first axis pos by 1/50th of its range" );
    grWriteln( "  F4        : increment first axis pos by 1/50th of its range" );
    grWriteln( "  F5        : decrement second axis pos by 1/50th of its range" );
    grWriteln( "  F6        : increment second axis pos by 1/50th of its range" );
    grWriteln( "  F7        : decrement third axis pos by 1/50th of its range" );
    grWriteln( "  F8        : increment third axis pos by 1/50th of its range" );
    grWriteln( "  F9        : decrement index by 100" );
    grWriteln( "  F10       : increment index by 100" );
    grWriteln( "  F11       : decrement index by 1000" );
    grWriteln( "  F12       : increment index by 1000" );
    grLn();
    grWriteln( "press any key to exit this help screen" );

    grRefreshSurface( surface );
    grListenSurface( surface, gr_event_key, &dummy_event );
  }
