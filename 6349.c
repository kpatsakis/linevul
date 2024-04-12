  int GetConsoleErrorCount() const {
    blink::mojom::ManifestManagerAssociatedPtr ptr;
    shell()
        ->web_contents()
        ->GetMainFrame()
        ->GetRemoteAssociatedInterfaces()
        ->GetInterface(&ptr);
    ptr.FlushForTesting();
    return console_error_count_;
  }
