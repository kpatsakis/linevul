  explicit EventFilterForPopupExit(RenderWidgetHostViewAura* rwhva)
      : rwhva_(rwhva) {
    DCHECK(rwhva_);
    aura::Env::GetInstance()->AddPreTargetHandler(this);
  }
