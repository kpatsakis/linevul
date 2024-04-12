void DataReductionProxyIOData::OnProxyConfigUpdated() {
  ui_task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(&DataReductionProxyService::SetConfiguredProxiesOnUI,
                     service_, config_->GetAllConfiguredProxies(),
                     config_->GetProxiesForHttp()));
  UpdateCustomProxyConfig();
  UpdateThrottleConfig();
}
