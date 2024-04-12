MockDataReductionProxyConfig::MockDataReductionProxyConfig(
    std::unique_ptr<DataReductionProxyConfigValues> config_values,
    scoped_refptr<base::SingleThreadTaskRunner> io_task_runner,
    scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner,
    DataReductionProxyConfigurator* configurator)
    : TestDataReductionProxyConfig(std::move(config_values),
                                   io_task_runner,
                                   ui_task_runner,
                                   configurator) {}
