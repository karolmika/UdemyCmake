#include "stdlib.h"
#include "stdio.h"

#include "parser.h"

static bool verify_payload(const uint8_t *payload, uint8_t len, uint8_t crc)
{
    uint8_t computed_crc = 0;
    for(uint8_t i=0; i<len; i++)
    {
        computed_crc += payload[i];
    }

    return (computed_crc == crc);
}

void parser_init(void)
{
    printf("Parser init !\n");
}

// 7E 03 A1 A2 A3 C9  7E 01 B4 8F  7E 00 00

void parser_feed(const uint8_t *data, size_t n, frame_cb_t cb)
{
    const uint8_t *payload = NULL;
    uint8_t len = 0;
    uint8_t crc = 0;

    printf("Parser feed !\n");
    for(size_t i=0; i<n; i++)
    {
        // printf("%d ", data[i]);
        if (FRAME_START_BYTE == data[i])
        {
            len = data[i+1];
            payload = (uint8_t*)&data[i+2];
            crc = data[i+2+len];
            break;
        }

    }
    bool result = verify_payload(payload, len, crc);

    if (result)
    {
        cb(payload, len);
    }
    printf("\n");
}
