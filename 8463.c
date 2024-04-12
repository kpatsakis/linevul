    BackingStoreEvents(Display* d, Picture pic, Pixmap pix,
                       const base::Closure& c)
        : display(d),
          picture(pic),
          pixmap(pix),
          closure(c) {
    }
