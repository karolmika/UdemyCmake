#pragma once
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define FRAME_START_BYTE 0x7E
#define PAYLOAD_MAX_SIZE 255

typedef void (*frame_cb_t)(const uint8_t *payload, uint8_t len);

void parser_init(void);
void parser_feed(const uint8_t *data, size_t n, frame_cb_t cb);
