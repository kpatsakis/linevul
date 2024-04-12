bool RilSapSocket::SocketExists(const char *socketName) {
 RilSapSocketList* current = head;

 while(NULL != current) {
 if(strcmp(current->socket->name, socketName) == 0) {
 return true;
 }
        current = current->next;
 }
 return false;
}
