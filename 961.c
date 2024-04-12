void Browser::RendererUnresponsive(TabContents* source) {
  browser::ShowHungRendererDialog(source);
}
