  static void VerifyAllTilesExistAndHavePile(
      const PictureLayerTiling* tiling,
      PicturePileImpl* pile) {
    for (PictureLayerTiling::CoverageIterator iter(
             tiling,
             tiling->contents_scale(),
             gfx::Rect(tiling->tiling_size()));
         iter;
         ++iter) {
      EXPECT_TRUE(*iter);
      EXPECT_EQ(pile, iter->raster_source());
    }
  }
