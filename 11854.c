 GLuint GetCubeServiceId(const TextureUnit& unit) {
   return unit.bound_texture_cube_map.get()
       ? unit.bound_texture_cube_map->service_id() : 0;
}
