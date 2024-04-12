mouse_scroll_line(void)
{
    if (relative_wheel_scroll)
	return (relative_wheel_scroll_ratio * LASTLINE + 99) / 100;
    else
	return fixed_wheel_scroll_count;
}
