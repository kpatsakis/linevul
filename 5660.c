void ContextState::UnbindTexture(TextureRef* texture) {
  GLuint active_unit = active_texture_unit;
  for (size_t jj = 0; jj < texture_units.size(); ++jj) {
    TextureUnit& unit = texture_units[jj];
    if (unit.bound_texture_2d.get() == texture) {
      unit.bound_texture_2d = NULL;
      if (active_unit != jj) {
        api()->glActiveTextureFn(GL_TEXTURE0 + jj);
        active_unit = jj;
      }
      api()->glBindTextureFn(GL_TEXTURE_2D, 0);
    } else if (unit.bound_texture_cube_map.get() == texture) {
      unit.bound_texture_cube_map = NULL;
      if (active_unit != jj) {
        api()->glActiveTextureFn(GL_TEXTURE0 + jj);
        active_unit = jj;
      }
      api()->glBindTextureFn(GL_TEXTURE_CUBE_MAP, 0);
    } else if (unit.bound_texture_external_oes.get() == texture) {
      unit.bound_texture_external_oes = NULL;
      if (active_unit != jj) {
        api()->glActiveTextureFn(GL_TEXTURE0 + jj);
        active_unit = jj;
      }
      api()->glBindTextureFn(GL_TEXTURE_EXTERNAL_OES, 0);
    } else if (unit.bound_texture_rectangle_arb.get() == texture) {
      unit.bound_texture_rectangle_arb = NULL;
      if (active_unit != jj) {
        api()->glActiveTextureFn(GL_TEXTURE0 + jj);
        active_unit = jj;
      }
      api()->glBindTextureFn(GL_TEXTURE_RECTANGLE_ARB, 0);
    } else if (unit.bound_texture_3d.get() == texture) {
      unit.bound_texture_3d = NULL;
      if (active_unit != jj) {
        api()->glActiveTextureFn(GL_TEXTURE0 + jj);
        active_unit = jj;
      }
      api()->glBindTextureFn(GL_TEXTURE_3D, 0);
    } else if (unit.bound_texture_2d_array.get() == texture) {
      unit.bound_texture_2d_array = NULL;
      if (active_unit != jj) {
        api()->glActiveTextureFn(GL_TEXTURE0 + jj);
        active_unit = jj;
      }
      api()->glBindTextureFn(GL_TEXTURE_2D_ARRAY, 0);
    }
  }

  if (active_unit != active_texture_unit) {
    api()->glActiveTextureFn(GL_TEXTURE0 + active_texture_unit);
  }
}
