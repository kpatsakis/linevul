  adisplay_done( ADisplay  display )
  {
    grDoneBitmap( display->bitmap );
    grDoneSurface( display->surface );

    display->bitmap  = NULL;
    display->surface = NULL;

    grDoneDevices();
  }
