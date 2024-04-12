static int serdes_phy_create(struct serdes_ctrl *ctrl, u8 idx, struct phy **phy)
{
	struct serdes_macro *macro;

	*phy = devm_phy_create(ctrl->dev, NULL, &serdes_ops);
	if (IS_ERR(*phy))
		return PTR_ERR(*phy);

	macro = devm_kzalloc(ctrl->dev, sizeof(*macro), GFP_KERNEL);
	if (!macro)
		return -ENOMEM;

	macro->idx = idx;
	macro->ctrl = ctrl;
	macro->port = -1;

	phy_set_drvdata(*phy, macro);

	return 0;
}
