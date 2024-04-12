flx_set_color (FlxColorSpaceConverter * flxpal, guint colr, guint red,
    guint green, guint blue, gint scale)
{

  g_return_if_fail (flxpal != NULL);
  g_return_if_fail (colr < 0x100);

  flxpal->palvec[(colr * 3)] = red << scale;
  flxpal->palvec[(colr * 3) + 1] = green << scale;
  flxpal->palvec[(colr * 3) + 2] = blue << scale;
}
