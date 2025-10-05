from socket import *
serverPort = 12000
serverSock = socket(AF_INET, SOCK_DGRAM)
serverSock.bind(('', serverPort))
print("server is ready")
while True:
    message, clientAddress = serverSock.recvfrom(2048)
    modifiedMessage = message.decode().upper()
    serverSock.sendto(modifiedMessage.encode(), clientAddress)
