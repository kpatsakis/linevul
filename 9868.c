void WebContentsViewAura::OverscrollUpdateForWebContentsDelegate(int delta_y) {
  if (web_contents_->GetDelegate() && IsScrollEndEffectEnabled())
    web_contents_->GetDelegate()->OverscrollUpdate(delta_y);
}
