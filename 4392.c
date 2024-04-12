static inline bool vrend_format_can_sample(enum virgl_formats format)
{
   return tex_conv_table[format].bindings & VREND_BIND_SAMPLER;
}
