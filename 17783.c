void RenderFrameHostImpl::GetFrameHostTestInterface(
    blink::mojom::FrameHostTestInterfaceRequest request) {
  class FrameHostTestInterfaceImpl
      : public blink::mojom::FrameHostTestInterface {
   public:
    void Ping(const GURL& url, const std::string& event) override {}
    void GetName(GetNameCallback callback) override {
      std::move(callback).Run("RenderFrameHostImpl");
    }
  };

  mojo::MakeStrongBinding(std::make_unique<FrameHostTestInterfaceImpl>(),
                          std::move(request));
}
