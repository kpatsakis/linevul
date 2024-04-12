   VoiceInteractionIcon() : Layer(ui::LAYER_NOT_DRAWN) {
     set_name("VoiceInteractionOverlay:ICON_LAYER");
    SetBounds(gfx::Rect(0, 0, kIconInitSizeDip, kIconInitSizeDip));
    SetFillsBoundsOpaquely(false);
    SetMasksToBounds(false);

    InitMoleculeShape();
   }
