#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define RING_BUF_SIZE   10

bool rb_push(uint8_t b);
bool rb_pop(uint8_t *b);
void ISR_mock(void);
void task_consumer(void);
uint8_t UART_read_data(void);
void print_env(void);
void rb_init(void);
