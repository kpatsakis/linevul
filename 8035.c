void DataReductionProxyIOData::SetPingbackReportingFraction(
    float pingback_reporting_fraction) {
  DCHECK(io_task_runner_->BelongsToCurrentThread());
  ui_task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(&DataReductionProxyService::SetPingbackReportingFraction,
                     service_, pingback_reporting_fraction));
}
