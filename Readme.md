# Reference implementation for proposed improved strings for C

(C) 2025 Niall Douglas [http://www.nedproductions.biz/](http://www.nedproductions.biz/)

CI: [![CI](https://github.com/ned14/wg14_strings/actions/workflows/ci.yml/badge.svg)](https://github.com/ned14/wg14_signals/actions/workflows/ci.yml)

Can be configured to be a standard library implementation for your
standard C library runtime. Licensed permissively.

This implements a variable length prefixed variable length array.
This quacks like `{ size_t length; uint8_t data[]; }` but instead
of always spending eight bytes on `length`, it can spend as little as a
single byte which makes it have no additional space overhead to a
null terminated byte string (NTBS).

Another useful feature is that the encoding of the variable length
prefix is 'UTF-8 aware' in that the encoding chosen is **guaranteed**
to parse as invalid UTF-8. This enables easier detection of when
variable length prefixed arrays are accidentally treated as NTBSs.

## Example of use

```c
static const char teststring[] = "Hello, I am a teapot!";

// You can allocate or fill a buffer supplied by you.
// This allocates an array with length of the string
// including trailing zero.
varuint8_t *arr = varuint8_malloc_ntbs(teststring);

// The number of items in the array
assert(varuint8_length(arr) == 22);

// The size of the array if you wanted to memcpy it
assert(varuint8_sizeof(arr) == 24);

// back would return the trailing zero of the string
assert(varuint8_back(arr) - varuint8_front(arr) == 21);

// You can index into the array
assert(*varuint8_index(arr, 4) == 'o');
assert(*varuint8_back(arr) == 0);

// If the array is null terminated and does not contain null
// characters, you can retrieve a null terminated string pointer.
assert(0 == strcmp(teststring, (char *) ntbs_from_varuint8(arr)));
free(arr);
```

## Supported targets

This library should work well on any POSIX implementation, as well as
Microsoft Windows.

Current CI test targets:

- Ubuntu Linux, x64.
- Mac OS, AArch64.
- Microsoft Windows, x64.

Current compilers:

- GCC
- clang
- MSVC

## Configuration

You can find a number of user definable macros to override in `config.h`.
They have sensible defaults on the major platforms and toolchains.

## Performance

### On my Threadripper 5975WX which is a 3.6Ghz processor bursting to 4.5Ghz on Linux:

`varuint8_fill()` takes 4.453511 nanoseconds.

`varuint8_length()` takes 1.109661 nanoseconds.

`varuint8_index()` takes 1.111395 nanoseconds.


### On a MacBook Pro M3 running ARM64

todo

### On a MacBook Pro M3 running ARM64 Windows within a VM

todo

# Todo

- `char8_from_varuint8_index()` does not yet check for invalid UTF-8 byte sequences,
it only checks for invalid UTF-8 single byte values.
