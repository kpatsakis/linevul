void Editor::RemoveFormattingAndStyle() {
  DCHECK(GetFrame().GetDocument());
  RemoveFormatCommand::Create(*GetFrame().GetDocument())->Apply();
}
