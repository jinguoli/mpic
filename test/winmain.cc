#include "test_common.h"

#ifdef WIN32
#include <WinSock2.h>

namespace {
struct OnApp {
    OnApp() {
        // Initialize net work.
        WSADATA wsaData;
        // Initialize Winsock 2.2
        int nError = WSAStartup(MAKEWORD(2, 2), &wsaData);

        if (nError) {
            std::cout << "WSAStartup() failed with error: %d" << nError;
        }

    }
    ~OnApp() {
        system("pause");
    }
} __s_onexit_pause;
}
#endif

// main function is defined on gtest_main.cc
