#include "stdlib.h"

#include "ring_buffer.h"

int main()
{
    // Clear buffer
    rb_init();

    for (size_t i = 0; i < 7; i++)
    {
        ISR_mock();
    }

    print_env();
    printf("\n");

    task_consumer();
    print_env();
    printf("\n");

    // ISR_mock();
    // print_env();
    // printf("\n");

    // task_consumer();
    // print_env();
    // printf("\n");

    return 0;
}

/*
cmake -S . -B build
cmake --build build
*/
