#include "wg14_strings/config.h"

#include <string.h>

struct varuint8_1_t
{
  uint8_t length[1];
  uint8_t data[];
};

struct varuint8_2_t
{
  uint8_t length[2];
  uint8_t data[];
};

struct varuint8_4_t
{
  uint8_t length[4];
  uint8_t data[];
};

struct varuint8_8_t
{
  uint8_t length[8];
  uint8_t data[];
};

size_t
WG14_STRING_PREFIX(varuint8_length)(const WG14_STRING_PREFIX(varuint8_t) * arr_)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  if(p->length[0] >= 0xf8 && p->length[0] <= 0xff)
  {
    return p->length[0] & 7;
  }
  if(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    return 8 + (a->length[1] & 0x3f);
  }
  if(0xf6 == p->length[0])
  {
    const struct varuint8_4_t *a = (const struct varuint8_4_t *) arr_;
    union
    {
      uint32_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint32_t *) a->length;
    return 72 + ((size_t) (x.b[3] & 0x3f) << 0) +
           ((size_t) (x.b[2] & 0x3f) << 6) + ((size_t) (x.b[1] & 0x3f) << 12);
  }
  if(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint64_t *) a->length;
    return 262216 + ((size_t) (x.b[7] & 0x3f) << 0) +
           ((size_t) (x.b[6] & 0x3f) << 6) + ((size_t) (x.b[5] & 0x3f) << 12) +
           ((size_t) (x.b[4] & 0x3f) << 18) + ((size_t) (x.b[3] & 0x3f) << 24) +
           ((size_t) (x.b[2] & 0x3f) << 30) + ((size_t) (x.b[1] & 0x3f) << 36);
  }
  return SIZE_MAX;
}

size_t
WG14_STRING_PREFIX(varuint8_sizeof)(const WG14_STRING_PREFIX(varuint8_t) * arr_)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  if(p->length[0] >= 0xf8 && p->length[0] <= 0xff)
  {
    return 1 + (p->length[0] & 7);
  }
  if(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    return 2 + 8 + (a->length[1] & 0x3f);
  }
  if(0xf6 == p->length[0])
  {
    const struct varuint8_4_t *a = (const struct varuint8_4_t *) arr_;
    union
    {
      uint32_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint32_t *) a->length;
    return 4 + 72 + ((size_t) (x.b[3] & 0x3f) << 0) +
           ((size_t) (x.b[2] & 0x3f) << 6) + ((size_t) (x.b[1] & 0x3f) << 12);
  }
  if(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint64_t *) a->length;
    return 8 + 262216 + ((size_t) (x.b[7] & 0x3f) << 0) +
           ((size_t) (x.b[6] & 0x3f) << 6) + ((size_t) (x.b[5] & 0x3f) << 12) +
           ((size_t) (x.b[4] & 0x3f) << 18) + ((size_t) (x.b[3] & 0x3f) << 24) +
           ((size_t) (x.b[2] & 0x3f) << 30) + ((size_t) (x.b[1] & 0x3f) << 36);
  }
  return SIZE_MAX;
}

uint8_t *WG14_STRING_PREFIX(varuint8_index)(WG14_STRING_PREFIX(varuint8_t) *
                                            arr_,
                                            size_t idx)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  if(p->length[0] >= 0xf8 && p->length[0] <= 0xff)
  {
    const size_t length = p->length[0] & 7;
    if(idx >= length)
    {
      return WG14_STRING_NULLPTR;
    }
    return ((uint8_t *) arr_) + 1 + idx;
  }
  if(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    const size_t length = 8 + (a->length[1] & 0x3f);
    if(idx >= length)
    {
      return WG14_STRING_NULLPTR;
    }
    return ((uint8_t *) arr_) + 2 + idx;
  }
  if(0xf6 == p->length[0])
  {
    const struct varuint8_4_t *a = (const struct varuint8_4_t *) arr_;
    union
    {
      uint32_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint32_t *) a->length;
    const size_t length = 72 + ((size_t) (x.b[3] & 0x3f) << 0) +
                          ((size_t) (x.b[2] & 0x3f) << 6) +
                          ((size_t) (x.b[1] & 0x3f) << 12);
    if(idx >= length)
    {
      return WG14_STRING_NULLPTR;
    }
    return ((uint8_t *) arr_) + 4 + idx;
  }
  if(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint64_t *) a->length;
    const size_t length =
    262216 + ((size_t) (x.b[7] & 0x3f) << 0) + ((size_t) (x.b[6] & 0x3f) << 6) +
    ((size_t) (x.b[5] & 0x3f) << 12) + ((size_t) (x.b[4] & 0x3f) << 18) +
    ((size_t) (x.b[3] & 0x3f) << 24) + ((size_t) (x.b[2] & 0x3f) << 30) +
    ((size_t) (x.b[1] & 0x3f) << 36);
    if(idx >= length)
    {
      return WG14_STRING_NULLPTR;
    }
    return ((uint8_t *) arr_) + 8 + idx;
  }
  return WG14_STRING_NULLPTR;
}

uint8_t *WG14_STRING_PREFIX(varuint8_front)(WG14_STRING_PREFIX(varuint8_t) *
                                            arr)
{
  return varuint8_index(arr, 0);
}

uint8_t *WG14_STRING_PREFIX(varuint8_back)(WG14_STRING_PREFIX(varuint8_t) *
                                           arr_)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  if(p->length[0] >= 0xf8 && p->length[0] <= 0xff)
  {
    const size_t length = p->length[0] & 7;
    return ((uint8_t *) arr_) + length;
  }
  if(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    const size_t length = 8 + (a->length[1] & 0x3f);
    return ((uint8_t *) arr_) + 1 + length;
  }
  if(0xf6 == p->length[0])
  {
    const struct varuint8_4_t *a = (const struct varuint8_4_t *) arr_;
    union
    {
      uint32_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint32_t *) a->length;
    const size_t length = 72 + ((size_t) (x.b[3] & 0x3f) << 0) +
                          ((size_t) (x.b[2] & 0x3f) << 6) +
                          ((size_t) (x.b[1] & 0x3f) << 12);
    return ((uint8_t *) arr_) + 3 + length;
  }
  if(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[4];
    } x;
    x.v = *(const uint64_t *) a->length;
    const size_t length =
    262216 + ((size_t) (x.b[7] & 0x3f) << 0) + ((size_t) (x.b[6] & 0x3f) << 6) +
    ((size_t) (x.b[5] & 0x3f) << 12) + ((size_t) (x.b[4] & 0x3f) << 18) +
    ((size_t) (x.b[3] & 0x3f) << 24) + ((size_t) (x.b[2] & 0x3f) << 30) +
    ((size_t) (x.b[1] & 0x3f) << 36);
    return ((uint8_t *) arr_) + 7 + length;
  }
  return WG14_STRING_NULLPTR;
}

char8_t *WG14_STRING_PREFIX(ntbs_from_varuint8)(WG14_STRING_PREFIX(varuint8_t) *
                                                arr)
{
  uint8_t *const back = varuint8_back(arr);
  if(back == WG14_STRING_NULLPTR || *back != 0)
  {
    return WG14_STRING_NULLPTR;
  }
  uint8_t *const front = varuint8_front(arr);
  if(back != memchr(front, 0, back - front))
  {
    return WG14_STRING_NULLPTR;
  }
  return (char8_t *) front;
}

char8_t *WG14_STRING_PREFIX(char8_from_varuint8_index)(
WG14_STRING_PREFIX(varuint8_t) * arr, size_t idx)
{
  uint8_t *p = varuint8_index(arr, idx);
  if(p == WG14_STRING_NULLPTR)
  {
    return WG14_STRING_NULLPTR;
  }
  for(;;)
  {
    switch(*p)
    {
      // Never should appear in valid UTF-8
    case 0xc0:
    case 0xc1:
    case 0xf5:
    case 0xf6:
    case 0xf7:
    case 0xf8:
    case 0xf9:
    case 0xfa:
    case 0xfb:
    case 0xfc:
    case 0xfd:
    case 0xfe:
    case 0xff:
      return WG14_STRING_NULLPTR;
    default:
      break;
    }
    // If a continuation byte, wind backwards
    if((*p & 0xc0) != 0x80)
    {
      return (char8_t *) p;
    }
    if(idx == 0)
    {
      return WG14_STRING_NULLPTR;
    }
    idx--;
    p--;
  }
}
