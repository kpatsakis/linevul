void TabStripGtk::DestroyDraggedTab(TabGtk* tab) {
  StopAnimation();

  std::vector<TabData>::iterator it = tab_data_.begin();
  for (; it != tab_data_.end(); ++it) {
    if (it->tab == tab) {
      if (!model_->closing_all())
        NOTREACHED() << "Leaving in an inconsistent state!";
      tab_data_.erase(it);
      break;
    }
  }

  gtk_container_remove(GTK_CONTAINER(tabstrip_.get()), tab->widget());
  MessageLoop::current()->DeleteSoon(FROM_HERE, tab);

  Layout();
}
