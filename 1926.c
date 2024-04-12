WebContents* ChromeWebContentsDelegateAndroid::OpenURLFromTab(
    WebContents* source,
    const content::OpenURLParams& params) {
  WindowOpenDisposition disposition = params.disposition;
  if (!source || (disposition != CURRENT_TAB &&
                  disposition != NEW_FOREGROUND_TAB &&
                  disposition != NEW_BACKGROUND_TAB &&
                  disposition != OFF_THE_RECORD &&
                  disposition != NEW_POPUP &&
                  disposition != NEW_WINDOW)) {
    return WebContentsDelegateAndroid::OpenURLFromTab(source, params);
  }

  Profile* profile = Profile::FromBrowserContext(source->GetBrowserContext());
  chrome::NavigateParams nav_params(profile,
                                    params.url,
                                    params.transition);
  FillNavigateParamsFromOpenURLParams(&nav_params, params);
  nav_params.source_contents = source;
  nav_params.window_action = chrome::NavigateParams::SHOW_WINDOW;
  nav_params.user_gesture = params.user_gesture;

  PopupBlockerTabHelper* popup_blocker_helper =
      PopupBlockerTabHelper::FromWebContents(source);
  DCHECK(popup_blocker_helper);

  if ((params.disposition == NEW_POPUP ||
       params.disposition == NEW_FOREGROUND_TAB ||
       params.disposition == NEW_BACKGROUND_TAB ||
       params.disposition == NEW_WINDOW) &&
      !params.user_gesture &&
      !base::CommandLine::ForCurrentProcess()->HasSwitch(
          switches::kDisablePopupBlocking)) {
    if (popup_blocker_helper->MaybeBlockPopup(nav_params,
                                              blink::WebWindowFeatures())) {
      return NULL;
    }
  }

  if (disposition == CURRENT_TAB) {
    nav_params.target_contents = source;
    prerender::PrerenderManager* prerender_manager =
        prerender::PrerenderManagerFactory::GetForProfile(profile);
    if (prerender_manager &&
        prerender_manager->MaybeUsePrerenderedPage(params.url, &nav_params)) {
      return nav_params.target_contents;
    }
  }

  return WebContentsDelegateAndroid::OpenURLFromTab(source, params);
}
