  TabContextMenuContents(BaseTab* tab,
                         BrowserTabStripController* controller)
      : tab_(tab),
        controller_(controller),
        last_command_(TabStripModel::CommandFirst) {
    model_.reset(new TabMenuModel(
        this, controller->model_,
        controller->tabstrip_->GetModelIndexOfBaseTab(tab)));
    menu_model_adapter_.reset(new views::MenuModelAdapter(model_.get()));
    menu_runner_.reset(
        new views::MenuRunner(menu_model_adapter_->CreateMenu()));
  }
