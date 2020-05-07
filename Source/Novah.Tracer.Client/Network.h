#pragma once

#include "NovahTracerEngine.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#include <memory>

#define GetMessage GetMessage // The Windows headers define "GetMessage" as "GetMessageW". Undo that.

enum class NetworkState
{
    Initialize,
    MessageReady,
    ReadingMessageType,
    ReadingMessageSize,
    ReadingMessage
};

class Network
{
private:
    WSADATA _wsaData;
    addrinfo* _addressInfoResult;
    SOCKET _connectedSocket;

    NetworkState _state;

    int _messageType;
    int _messageTypeRead;

    int _messageSize;
    int _messageSizeRead;

    std::unique_ptr<const char[]> _message;
    int _messageRead;

    void Read();
    bool IsMessageReady() const;

public:
    Network(const char* ip, const char* port);
    ~Network();

    int Send(const char* buffer, int bufferSizeInBytes) const;
    void SendChunkRequestedMessage() const;

    std::unique_ptr<const char[]> GetMessage();
};