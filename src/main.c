#include "engine.h"

/**
 * todo:
 *  - figure import memory leaks
 *  - look at deep copy functions
 *  - check const correctness entire project
 *  - check memory handling entire project
 *  - support import of object with different amount of faces
 *  - colors
 *  - config file
 */

// linux
int main(int argc, char **argv) {
    engine_run();
    return 0;
}

// windows
int WinMain(int argc, char **argv) {
    engine_run();
    return 0;
}
