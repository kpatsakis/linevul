gst_asf_demux_descramble_buffer (GstASFDemux * demux, AsfStream * stream,
    GstBuffer ** p_buffer)
{
  GstBuffer *descrambled_buffer;
  GstBuffer *scrambled_buffer;
  GstBuffer *sub_buffer;
  guint offset;
  guint off;
  guint row;
  guint col;
  guint idx;

  /* descrambled_buffer is initialised in the first iteration */
  descrambled_buffer = NULL;
  scrambled_buffer = *p_buffer;

  if (gst_buffer_get_size (scrambled_buffer) <
      stream->ds_packet_size * stream->span)
    return;

  for (offset = 0; offset < gst_buffer_get_size (scrambled_buffer);
      offset += stream->ds_chunk_size) {
    off = offset / stream->ds_chunk_size;
    row = off / stream->span;
    col = off % stream->span;
    idx = row + col * stream->ds_packet_size / stream->ds_chunk_size;
    GST_DEBUG ("idx=%u, row=%u, col=%u, off=%u, ds_chunk_size=%u", idx, row,
        col, off, stream->ds_chunk_size);
    GST_DEBUG ("scrambled buffer size=%" G_GSIZE_FORMAT
        ", span=%u, packet_size=%u", gst_buffer_get_size (scrambled_buffer),
        stream->span, stream->ds_packet_size);
    GST_DEBUG ("gst_buffer_get_size (scrambled_buffer) = %" G_GSIZE_FORMAT,
        gst_buffer_get_size (scrambled_buffer));
    sub_buffer =
        gst_buffer_copy_region (scrambled_buffer, GST_BUFFER_COPY_MEMORY,
        idx * stream->ds_chunk_size, stream->ds_chunk_size);
    if (!offset) {
      descrambled_buffer = sub_buffer;
    } else {
      descrambled_buffer = gst_buffer_append (descrambled_buffer, sub_buffer);
    }
  }

  GST_BUFFER_TIMESTAMP (descrambled_buffer) =
      GST_BUFFER_TIMESTAMP (scrambled_buffer);
  GST_BUFFER_DURATION (descrambled_buffer) =
      GST_BUFFER_DURATION (scrambled_buffer);
  GST_BUFFER_OFFSET (descrambled_buffer) = GST_BUFFER_OFFSET (scrambled_buffer);
  GST_BUFFER_OFFSET_END (descrambled_buffer) =
      GST_BUFFER_OFFSET_END (scrambled_buffer);

  /* FIXME/CHECK: do we need to transfer buffer flags here too? */

  gst_buffer_unref (scrambled_buffer);
  *p_buffer = descrambled_buffer;
}
