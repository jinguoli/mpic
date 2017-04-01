#include <sys/types.h>
#include <assert.h>
#include <signal.h>
#include <string.h>
#include <stdio.h>

#include "mpic/exp.h"
#include "mpic/master.h"
#include "mpic/title.h"

#ifdef H_OS_WINDOWS
#pragma comment(lib,"libglog_static.lib")
#endif


void sigterm(int c) {
    std::string title_prefix = mpic::Option::GetExeName() + "(" + mpic::Master::instance().option()->name() + "): worker process is shutting down ...";
    mpic::Title::Set(title_prefix);
    sleep(5); // so we can use 'ps' to watch the status fo this process when it is shutting down.
    exit(0);
}

// Run on Windowns:
//      $ cd vsprojects/bin/Debug
//      $ ./mpic-framework.exe --cfg=mpic.conf --mod=libechomod.dll
//
// Run on Linux
//      $ ./mpic-framework --mod=../modules/echo/libechomodule.so -f
//      $ ./bin/examples_mpic_framework --cfg=/tmp/mpic.conf --mod=/home/weizili/git/mpic/build/lib/libexamples_module_echo.so -f
//
int main(int argc, char* argv[]) {
    signal(SIGTERM, &sigterm);
    std::shared_ptr<mpic::Option> op(new mpic::Option);
    mpic::Master& pm = mpic::Master::instance();
    if (pm.Init(argc, argv, op)) {
        return pm.Run();
    } else {
        LOG(ERROR) << "master init failed.";
        return -1;
    }
}
