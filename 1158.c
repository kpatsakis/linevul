ServiceWorkerPaymentInstrument::ServiceWorkerPaymentInstrument(
    content::BrowserContext* browser_context,
    const GURL& top_origin,
    const GURL& frame_origin,
    const PaymentRequestSpec* spec,
    std::unique_ptr<content::StoredPaymentApp> stored_payment_app_info,
    PaymentRequestDelegate* payment_request_delegate)
    : PaymentInstrument(0, PaymentInstrument::Type::SERVICE_WORKER_APP),
      browser_context_(browser_context),
      top_origin_(top_origin),
      frame_origin_(frame_origin),
      spec_(spec),
      stored_payment_app_info_(std::move(stored_payment_app_info)),
      delegate_(nullptr),
      payment_request_delegate_(payment_request_delegate),
      can_make_payment_result_(false),
      has_enrolled_instrument_result_(false),
      needs_installation_(false),
      weak_ptr_factory_(this) {
  DCHECK(browser_context_);
  DCHECK(top_origin_.is_valid());
  DCHECK(frame_origin_.is_valid());
  DCHECK(spec_);

  if (stored_payment_app_info_->icon) {
    icon_image_ =
        gfx::ImageSkia::CreateFrom1xBitmap(*(stored_payment_app_info_->icon))
            .DeepCopy();
  } else {
    icon_image_ = gfx::ImageSkia::CreateFrom1xBitmap(SkBitmap()).DeepCopy();
  }
}
