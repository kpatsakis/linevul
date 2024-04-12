void HostPortAllocatorSession::ConfigReady(cricket::PortConfiguration* config) {
  for (cricket::PortConfiguration::RelayList::iterator relay =
           config->relays.begin(); relay != config->relays.end(); ++relay) {
    cricket::PortConfiguration::PortList filtered_ports;
    for (cricket::PortConfiguration::PortList::iterator port =
             relay->ports.begin(); port != relay->ports.end(); ++port) {
      if (port->proto == cricket::PROTO_UDP) {
        filtered_ports.push_back(*port);
      }
    }
    relay->ports = filtered_ports;
  }
  cricket::BasicPortAllocatorSession::ConfigReady(config);
}
