#include <stdlib.h>
#include <stdio.h>

//#define USE_PSEUDO_RANDOM
#ifdef USE_PSEUDO_RANDOM
#include "mini_random.h"
#else 
#include "mini_random_win.h"
#endif

static void test_random();

int main(void) 
{
    test_random();

    getchar();

    return 0;
}

void test_random()
{
#ifdef USE_PSEUDO_RANDOM
    for (int i = 0; i < 10; ++i) {
        printf("random number: %d\n", minilib::gen_random());
    }

    minilib::Random random;
    for (int i = 0; i < 10; ++i) {
        printf("Random class gen number: %d\n", random.getRandom());
    }
#else 
    do {
        if (!minilib::init_rand_ctx()) {
            printf("init rand context failed!");
            break;
        }

        for (int i = 0; i < 10; ++i) {
            printf("random number: %u\n", (unsigned)minilib::gen_win_random());
        }

        minilib::unit_rand_ctx();
    } while (0);


    minilib::RandomWin random;
    for (int i = 0; i < 10; ++i) {
        printf("RandomWin class gen number: %u\n", (unsigned)random.getRandom());
    }
#endif
}
