  void NotifyRefreshNetwork() {
    ash::NetworkObserver* observer = tray_->network_observer();
    chromeos::NetworkLibrary* crosnet =
        chromeos::CrosLibrary::Get()->GetNetworkLibrary();
    if (observer) {
      ash::NetworkIconInfo info;
      info.image = network_icon_->GetIconAndText(&info.description);
      info.tray_icon_visible =
          ShouldShowNetworkIconInTray(crosnet->connected_network());
      observer->OnNetworkRefresh(info);
    }

    const Network* connected_network = crosnet->connected_network();
    if (accessibility::IsSpokenFeedbackEnabled()) {
      bool speak = false;
      if (connected_network_ != connected_network) {
        speak = true;
      } else if (connected_network) {
        if ((Network::IsConnectedState(state_) &&
             !connected_network->connected()) ||
            (Network::IsConnectingState(state_) &&
             !connected_network->connecting()) ||
            (Network::IsDisconnectedState(state_) &&
             !connected_network->disconnected())) {
          speak = true;
        }
      }

      if (speak) {
        AccessibilitySpeak(connected_network);
      }
    }

    connected_network_ = connected_network;
    if (connected_network) {
      state_ = connected_network->state();
    } else {
      state_ = STATE_UNKNOWN;
    }
  }
