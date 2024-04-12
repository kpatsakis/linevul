bool IsOutOfProcessNetworkService() {
  return base::FeatureList::IsEnabled(network::features::kNetworkService) &&
         !base::FeatureList::IsEnabled(features::kNetworkServiceInProcess) &&
         !base::CommandLine::ForCurrentProcess()->HasSwitch(
             switches::kSingleProcess);
}
