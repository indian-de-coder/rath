#pragma once

#include "Beacon/Beacon.hpp"
#include "Battery/Battery.hpp"

class TCPShell
{
private:
    int server_socket;
    Battery& battery;
    Beacon& beacon;

    void run();

    static void task(void *arg);

public:
    TCPShell(Beacon& beacon, Battery& battery);

    void start();
};