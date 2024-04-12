views::Link* CreateLink(const base::string16& link_text,
                        views::LinkListener* listener) {
  views::Link* link_button = new views::Link(link_text);
  link_button->SetHorizontalAlignment(gfx::ALIGN_LEFT);
  link_button->SetUnderline(false);
  link_button->set_listener(listener);
  return link_button;
}
