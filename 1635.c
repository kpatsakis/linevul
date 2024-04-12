bool ATSParser::PTSTimeDeltaEstablished() {
 if (mPrograms.isEmpty()) {
 return false;
 }

 return mPrograms.editItemAt(0)->PTSTimeDeltaEstablished();
}
