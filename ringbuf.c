#include <stdio.h>
#include <stdint.h>

#define BUF_SIZE 8
#define MASK (BUF_SIZE - 1)

typedef struct {
    uint8_t data[BUF_SIZE];
    uint8_t head, tail, count;
} RingBuffer;

void buf_init(RingBuffer *buf) {
    buf->head = buf->tail = buf->count = 0;
}

// Returns 1 (Success) or 0 (Fail)
int buf_write(RingBuffer *buf, uint8_t val) {
    if (buf->count == BUF_SIZE) return 0; 
    
    buf->data[buf->head] = val;
    buf->head = (buf->head + 1) & MASK; // O(1) Bitwise wrap-around
    buf->count++;
    
    return 1;
}

// Returns 1 (Success) or 0 (Fail)
int buf_read(RingBuffer *buf, uint8_t *val) {
    if (buf->count == 0) return 0;
    
    *val = buf->data[buf->tail];
    buf->tail = (buf->tail + 1) & MASK; // O(1) Bitwise wrap-around
    buf->count--;
    
    return 1;
}

int main(void) {
    RingBuffer buf;
    buf_init(&buf);
    uint8_t val;

    // 1. Write 8 bytes (0x41 to 0x48)
    for (uint8_t i = 0x41; i <= 0x48; i++) {
        buf_write(&buf, i);
        // Ternary operator instantly adds " FULL" if count hits 8
        printf("[WRITE] 0x%02X -> OK (count=%u)%s\n", i, buf.count, buf.count == BUF_SIZE ? " FULL" : "");
    }

    // 2. Attempt overflow write (0x99)
    if (!buf_write(&buf, 0x99)) 
    printf("[WRITE] 0x99 -> FAIL (buffer full)\n");

    // 3. Read 3 bytes
    for (int i = 0; i < 3; i++) {
        if (buf_read(&buf, &val))
         printf("[READ]       -> 0x%02X (count=%u)\n", val, buf.count);
    }

    // 4. Write 3 new bytes (0x49 to 0x4B)
    for (uint8_t i = 0x49; i <= 0x4B; i++) {
        buf_write(&buf, i);
        printf("[WRITE] 0x%02X -> OK (count=%u)%s\n", i, buf.count, buf.count == BUF_SIZE ? " FULL" : "");
    }

    // 5. Read all remaining bytes
    while (buf_read(&buf, &val)) {
        printf("[READ]       -> 0x%02X (count=%u)\n", val, buf.count);
    }

    // 6. Attempt underflow read
    if (!buf_read(&buf, &val))
     printf("[READ] (empty) -> FAIL (buffer empty)\n");

    return 0;
}