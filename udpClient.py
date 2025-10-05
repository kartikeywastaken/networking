from socket import *
serverName = "127.0.0.1"
serverPort = 12000
clientSock = socket(AF_INET, SOCK_DGRAM)
message  = input('Input lowercase sentence:\n')
clientSock.sendto(message.encode(), (serverName, serverPort))
modifiedMessage, serverAddress = clientSock.recvfrom(2048)
print(modifiedMessage.decode())
clientSock.close()
