/* Run real game input paths with fixed events and without animation pauses. */
#include <stdlib.h>
#include <unistd.h>
static unsigned int no_sleep(unsigned int seconds) { (void)seconds; return 0; }
static int no_usleep(useconds_t delay) { (void)delay; return 0; }
static int fixed_rand(void) { return 3; }
#define sleep no_sleep
#define usleep no_usleep
#define rand fixed_rand
#include "../tamagoshi cow.c"
