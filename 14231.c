void RenderMediaClient::RecordRapporURL(const std::string& metric,
                                        const GURL& url) {
   GetContentClient()->renderer()->RecordRapporURL(metric, url);
 }
