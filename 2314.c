  bool HasMediaRouterActionAtInit() const {
    const std::set<std::string>& component_ids =
        ToolbarActionsModel::Get(browser()->profile())
            ->component_actions_factory()
            ->GetInitialComponentIds();

    return base::ContainsKey(
        component_ids, ComponentToolbarActionsFactory::kMediaRouterActionId);
  }
