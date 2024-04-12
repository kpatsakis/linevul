GURL LinkDoctorBaseURL() {
  if (gUseMockLinkDoctorBaseURLForTesting)
    return GURL("http://mock.linkdoctor.url/for?testing");
  return GURL(LINKDOCTOR_SERVER_REQUEST_URL);
}
