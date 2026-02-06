#include "stdlib.h"
#include "stdio.h"

#include "ring_buffer.h"

uint8_t ring_buffer[RING_BUF_SIZE];
volatile uint8_t rb_head;
volatile uint8_t rb_tail;
volatile uint32_t rb_dropped_data_count;

static size_t rb_count(uint8_t h, uint8_t t);

static inline uint8_t inc(uint8_t v) {
    v++;
    if (v >= RING_BUF_SIZE) v = 0;
    return v;
}

void print_env(void)
{
    // make copy to avoid hazard race with ISR
    uint8_t head = rb_head;
    uint8_t tail = rb_tail;
    size_t cnt = rb_count(head, tail);
    printf("[H=%d, T=%d, C=%ld, Buffer= ", head, tail, cnt);

    for(int i=0; i<cnt; i++)
    {
        printf("%d, ", ring_buffer[tail++]);
        if (tail >= RING_BUF_SIZE)
        {
            tail = 0;
        }
    }
    printf("]\n");
}

void task_consumer(void)
{
    printf("task consumer called !\n");
    uint8_t data;

    // enter_critical_secion() / ISR_disable()
    while (rb_pop(&data))
    {
        printf("New data: %d\n", data);
    }
    // exit_critical_secion() / ISR_enable()
}

void rb_init(void)
{
    memset(ring_buffer, 0x00, RING_BUF_SIZE);
    rb_head = 0;
    rb_tail = 0;
    rb_dropped_data_count = 0;
}

bool rb_pop(uint8_t *b)
{
    bool result = false;
    static int isr_interrupt_cnt = 0;

    // if(rb_count(rb_head, rb_tail) > 0)
    if(rb_head != rb_tail)
    {
        // This simulates situation where ISR interrupts rb_pop
        if (!isr_interrupt_cnt)
        {
            ISR_mock();         // only once
            isr_interrupt_cnt++;
        }

        *b = ring_buffer[rb_tail];
        rb_tail++;

        if(rb_tail >= RING_BUF_SIZE)
        {
            rb_tail = 0;
        }
        result = true;
    }
    return result;
}

size_t rb_count(uint8_t h, uint8_t t)
{
    size_t diff = 0;
    if(h != t)
    {
        if(h > t)
        {
            diff = h - t;
        }
        else
        {
            diff = RING_BUF_SIZE - (t - h);
        }
    }

    return diff;
}

void ISR_mock(void)
{
    uint8_t new_data = UART_read_data();
    rb_push(new_data);
    printf("ISR called ! New data: %d\n", new_data);
}

uint8_t UART_read_data(void)
{
    return rand() % 255;
}

bool rb_push(uint8_t b)
{
    bool result = false;
    // make copy to avoid hazard race with ISR
    uint8_t tail = rb_tail;

    // check if head touches tail
    uint8_t next_item = 0;

    if (rb_head < (RING_BUF_SIZE - 1))
    {
        next_item = rb_head + 1;
    }

    if(next_item != tail)
    {
        ring_buffer[rb_head] = b;

        // enter critical secion / ISR disable
        rb_head = inc(rb_head);
        // exti critical secion / ISR enable
        result = true;

        if (rb_dropped_data_count > 0)
        {
            rb_dropped_data_count = 0;
        }

    }
    else
    {
        rb_dropped_data_count++;
    }

    return result;
}

/*
uint8_t diff_head = rb_head_copy - rb_head;
rb_head_copy = rb_head;
*/
