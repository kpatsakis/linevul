void DataReductionProxyIOData::SetIgnoreLongTermBlackListRules(
    bool ignore_long_term_black_list_rules) {
  ui_task_runner_->PostTask(
      FROM_HERE,
      base::BindOnce(
          &DataReductionProxyService::SetIgnoreLongTermBlackListRules, service_,
          ignore_long_term_black_list_rules));
}
