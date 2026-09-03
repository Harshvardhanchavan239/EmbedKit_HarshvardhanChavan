# EmbedKit Harshvardhan Chavan

This repository contains a simple **C implementation of a fixed-size ring buffer** (circular buffer) for `uint8_t` data.

## File Structure

- `/home/runner/work/EmbedKit_HarshvardhanChavan/EmbedKit_HarshvardhanChavan/ringbuf.c`  
  Implements the ring buffer and includes a small demo in `main()`.

## Features

- Constant-time (`O(1)`) read/write operations
- Bitmask-based wrap-around for efficient indexing
- Overflow and underflow handling
- Demo flow showing:
  - Filling the buffer
  - Overflow write attempt
  - Partial reads
  - Wrap-around writes
  - Full drain and underflow read attempt

## Buffer Configuration

The buffer is configured in `ringbuf.c`:

- `BUF_SIZE = 8`
- `MASK = BUF_SIZE - 1`

> Note: The bitmask wrap-around method assumes `BUF_SIZE` is a power of two.

## Build and Run

From the repository root:

```bash
gcc  ringbuf.c -o ringbuf.exe
```

## Ring Buffer API

- `void buf_init(RingBuffer *buf)`  
  Initializes buffer indices and count.

- `int buf_write(RingBuffer *buf, uint8_t val)`  
  Writes one byte if space is available.  
  Returns `1` on success, `0` if full.

- `int buf_read(RingBuffer *buf, uint8_t *val)`  
  Reads one byte if data is available.  
  Returns `1` on success, `0` if empty.
