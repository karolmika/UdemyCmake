# Task is to write Robust framed protocol parser. 

You receive bytes from a stream (UART, SPI, TCP, DMA chunks, etc.). Data may arrive:
- in arbitrary chunk sizes
- split across calls
- with noise or corrupted frames

Frame format is:
```
0x7E | LEN | PAYLOAD[LEN] | CRC
```
Start byte has value ```0x7E``, than 1 byte len, payload nad 1 byte CRC.
Frames can arrive with no gap at all between them

# Required API

```
typedef void (*frame_cb_t)(const uint8_t *payload, uint8_t len);

void parser_init(void);
void parser_feed(const uint8_t *data, size_t n, frame_cb_t cb);
```

# Constraints

Constraints (assume interviewer conditions) are as follow:
- Cortex-M class MCU
- No malloc
- Parser state must survive across calls
- CRC polynomial is your choice (just be consistent)
