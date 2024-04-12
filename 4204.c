void BrowserRenderProcessHost::OnSavedPageAsMHTML(int job_id, bool success) {
  content::GetContentClient()->browser()->GetMHTMLGenerationManager()->
      MHTMLGenerated(job_id, success);
}
