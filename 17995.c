static void flush_packet(vorb *f)
{
   while (get8_packet_raw(f) != EOP);
}
