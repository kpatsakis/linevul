  void IsCalloutAboveLauncherIcon(aura::Window* panel) {
    base::RunLoop().RunUntilIdle();
    views::Widget* widget = GetCalloutWidgetForPanel(panel);

    Shelf* shelf = GetShelfForWindow(panel);
    gfx::Rect icon_bounds = shelf->GetScreenBoundsOfItemIconForWindow(panel);
    ASSERT_FALSE(icon_bounds.IsEmpty());

    gfx::Rect panel_bounds = panel->GetBoundsInScreen();
    gfx::Rect callout_bounds = widget->GetWindowBoundsInScreen();
    ASSERT_FALSE(icon_bounds.IsEmpty());

    EXPECT_TRUE(widget->IsVisible());

    const ShelfAlignment alignment = shelf->alignment();
    if (alignment == SHELF_ALIGNMENT_LEFT)
      EXPECT_EQ(panel_bounds.x(), callout_bounds.right());
    else if (alignment == SHELF_ALIGNMENT_RIGHT)
      EXPECT_EQ(panel_bounds.right(), callout_bounds.x());
    else
      EXPECT_EQ(panel_bounds.bottom(), callout_bounds.y());

    if (IsHorizontal(alignment)) {
      EXPECT_NEAR(icon_bounds.CenterPoint().x(),
                  widget->GetWindowBoundsInScreen().CenterPoint().x(), 1);
    } else {
      EXPECT_NEAR(icon_bounds.CenterPoint().y(),
                  widget->GetWindowBoundsInScreen().CenterPoint().y(), 1);
    }
  }
