#include "wg14_strings/config.h"

#include <assert.h>
#include <stdlib.h>

#ifdef _MSC_VER
#pragma warning(disable : 4200)  // zero-sized array in struct/union
#endif

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

static inline uint8_t *internal_fill(void *buf, size_t buflen, size_t datalen)
{
  const size_t headerlen = WG14_STRING_PREFIX(varuint8_header_size)(datalen);
  if(datalen + headerlen > buflen)
  {
    return WG14_STRING_NULLPTR;
  }
  switch(headerlen)
  {
  case 1:
  {
    assert(datalen < 8);
    struct varuint8_1_t *a = (struct varuint8_1_t *) buf;
    a->length[0] = (uint8_t) (0xf8 + datalen);
    return a->data;
  }
  case 2:
  {
    assert(datalen < 72);
    struct varuint8_2_t *a = (struct varuint8_2_t *) buf;
    a->length[0] = (uint8_t) (0xf5);
    a->length[1] = (uint8_t) (0x80 | (datalen - 8));
    return a->data;
  }
  case 4:
  {
    assert(datalen < 262216);
    struct varuint8_4_t *a = (struct varuint8_4_t *) buf;
    a->length[0] = (uint8_t) (0xf6);
    const size_t l = datalen - 72;
    a->length[1] = (uint8_t) (0x80 | ((l >> 12) & 0x3f));
    a->length[2] = (uint8_t) (0x80 | ((l >> 6) & 0x3f));
    a->length[3] = (uint8_t) (0x80 | ((l >> 0) & 0x3f));
    return a->data;
  }
  case 8:
  {
    assert(datalen < 4398046773319ULL);
    struct varuint8_8_t *a = (struct varuint8_8_t *) buf;
    a->length[0] = (uint8_t) (0xf7);
    const size_t l = datalen - 262216;
    a->length[1] = (uint8_t) (0x80 | ((l >> 36) & 0x3f));
    a->length[2] = (uint8_t) (0x80 | ((l >> 30) & 0x3f));
    a->length[3] = (uint8_t) (0x80 | ((l >> 24) & 0x3f));
    a->length[4] = (uint8_t) (0x80 | ((l >> 18) & 0x3f));
    a->length[5] = (uint8_t) (0x80 | ((l >> 12) & 0x3f));
    a->length[6] = (uint8_t) (0x80 | ((l >> 6) & 0x3f));
    a->length[7] = (uint8_t) (0x80 | ((l >> 0) & 0x3f));
    return a->data;
  }
  default:
    return WG14_STRING_NULLPTR;
  }
}

WG14_STRING_PREFIX(varuint8_t) *
WG14_STRING_PREFIX(varuint8_fill)(void *buf, size_t buflen, const uint8_t *data,
                                  size_t datalen)
{
  uint8_t *dest = internal_fill(buf, buflen, datalen);
  if(dest == WG14_STRING_NULLPTR)
  {
    return WG14_STRING_NULLPTR;
  }
  if(datalen > 0)
  {
    memcpy(dest, data, datalen);
  }
  return (WG14_STRING_PREFIX(varuint8_t) *) buf;
}

WG14_STRING_PREFIX(varuint8_t) *
WG14_STRING_PREFIX(varuint8_malloc)(const uint8_t *data, size_t datalen)
{
  const size_t headerlen = WG14_STRING_PREFIX(varuint8_header_size)(datalen);
  void *ret = malloc(datalen + headerlen);
  if(ret == WG14_STRING_NULLPTR)
  {
    return WG14_STRING_NULLPTR;
  }
  return WG14_STRING_PREFIX(varuint8_fill)(ret, datalen + headerlen, data,
                                           datalen);
}

WG14_STRING_PREFIX(varuint8_t) *
WG14_STRING_PREFIX(varuint8_cat_N)(
void *buf, size_t buflen, const WG14_STRING_PREFIX(varuint8_t) *const *arrs,
size_t arrslen)
{
  size_t totallen = 0;
  for(size_t n = 0; n < arrslen; n++)
  {
    totallen += WG14_STRING_PREFIX(varuint8_length)(arrs[n]);
  }
  const size_t headerlen = WG14_STRING_PREFIX(varuint8_header_size)(totallen);
  if(totallen + headerlen > buflen)
  {
    return WG14_STRING_NULLPTR;
  }
  uint8_t *dest = internal_fill(buf, buflen, totallen);
  if(dest == WG14_STRING_NULLPTR)
  {
    return WG14_STRING_NULLPTR;
  }
  if(totallen > 0)
  {
    for(size_t n = 0; n < arrslen; n++)
    {
      const size_t srclen = WG14_STRING_PREFIX(varuint8_length)(arrs[n]);
      if(srclen > 0)
      {
        const uint8_t *src = WG14_STRING_PREFIX(varuint8_front)(
        (WG14_STRING_PREFIX(varuint8_t) *) arrs[n]);
        memcpy(dest, src, srclen);
        dest += srclen;
      }
    }
  }
  return (WG14_STRING_PREFIX(varuint8_t) *) buf;
}


WG14_STRING_PREFIX(varuint8_t) *
WG14_STRING_PREFIX(varuint8_dup)(const WG14_STRING_PREFIX(varuint8_t) * arr)
{
  const size_t totallen = WG14_STRING_PREFIX(varuint8_sizeof)(arr);
  void *ret = malloc(totallen);
  if(ret == WG14_STRING_NULLPTR)
  {
    return WG14_STRING_NULLPTR;
  }
  memcpy(ret, arr, totallen);
  return (WG14_STRING_PREFIX(varuint8_t) *) ret;
}

size_t
WG14_STRING_PREFIX(varuint8_length)(const WG14_STRING_PREFIX(varuint8_t) * arr_)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  WG14_STRING_IF_LIKELY(p->length[0] >= 0xf8)
  {
    return p->length[0] & 7;
  }
  WG14_STRING_IF_LIKELY(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    return 8 + (a->length[1] & 0x3f);
  }
  WG14_STRING_IF_LIKELY(0xf6 == p->length[0])
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
  WG14_STRING_IF_LIKELY(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[8];
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
  WG14_STRING_IF_LIKELY(p->length[0] >= 0xf8)
  {
    return 1 + (p->length[0] & 7);
  }
  WG14_STRING_IF_LIKELY(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    return 2 + 8 + (a->length[1] & 0x3f);
  }
  WG14_STRING_IF_LIKELY(0xf6 == p->length[0])
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
  WG14_STRING_IF_LIKELY(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[8];
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
  WG14_STRING_IF_LIKELY(p->length[0] >= 0xf8)
  {
    const size_t length = p->length[0] & 7;
    if(idx >= length)
    {
      return WG14_STRING_NULLPTR;
    }
    return (uint8_t *) p->data + idx;
  }
  WG14_STRING_IF_LIKELY(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    const size_t length = 8 + (a->length[1] & 0x3f);
    if(idx >= length)
    {
      return WG14_STRING_NULLPTR;
    }
    return (uint8_t *) a->data + idx;
  }
  WG14_STRING_IF_LIKELY(0xf6 == p->length[0])
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
    return (uint8_t *) a->data + idx;
  }
  WG14_STRING_IF_LIKELY(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[8];
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
    return (uint8_t *) a->data + idx;
  }
  return WG14_STRING_NULLPTR;
}

uint8_t *WG14_STRING_PREFIX(varuint8_front)(WG14_STRING_PREFIX(varuint8_t) *
                                            arr_)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  WG14_STRING_IF_LIKELY(p->length[0] >= 0xf8)
  {
    const size_t length = p->length[0] & 7;
    if(0 == length)
    {
      return WG14_STRING_NULLPTR;
    }
    return (uint8_t *) p->data;
  }
  WG14_STRING_IF_LIKELY(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    return (uint8_t *) a->data;
  }
  WG14_STRING_IF_LIKELY(0xf6 == p->length[0])
  {
    const struct varuint8_4_t *a = (const struct varuint8_4_t *) arr_;
    return (uint8_t *) a->data;
  }
  WG14_STRING_IF_LIKELY(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    return (uint8_t *) a->data;
  }
  return WG14_STRING_NULLPTR;
}

uint8_t *WG14_STRING_PREFIX(varuint8_back)(WG14_STRING_PREFIX(varuint8_t) *
                                           arr_)
{
  const struct varuint8_1_t *p = (const struct varuint8_1_t *) arr_;
  WG14_STRING_IF_LIKELY(p->length[0] >= 0xf8)
  {
    const size_t length = p->length[0] & 7;
    if(0 == length)
    {
      return WG14_STRING_NULLPTR;
    }
    return (uint8_t *) p->data + length - 1;
  }
  WG14_STRING_IF_LIKELY(0xf5 == p->length[0])
  {
    const struct varuint8_2_t *a = (const struct varuint8_2_t *) arr_;
    const size_t length = 8 + (a->length[1] & 0x3f);
    return (uint8_t *) a->data + length - 1;
  }
  WG14_STRING_IF_LIKELY(0xf6 == p->length[0])
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
    return (uint8_t *) a->data + length - 1;
  }
  WG14_STRING_IF_LIKELY(0xf7 == p->length[0])
  {
    const struct varuint8_8_t *a = (const struct varuint8_8_t *) arr_;
    union
    {
      uint64_t v;
      uint8_t b[8];
    } x;
    x.v = *(const uint64_t *) a->length;
    const size_t length =
    262216 + ((size_t) (x.b[7] & 0x3f) << 0) + ((size_t) (x.b[6] & 0x3f) << 6) +
    ((size_t) (x.b[5] & 0x3f) << 12) + ((size_t) (x.b[4] & 0x3f) << 18) +
    ((size_t) (x.b[3] & 0x3f) << 24) + ((size_t) (x.b[2] & 0x3f) << 30) +
    ((size_t) (x.b[1] & 0x3f) << 36);
    return (uint8_t *) a->data + length - 1;
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
  if(back != memchr(front, 0, back - front + 1))
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
    // TODO: Check for other illegal sequences of two bytes
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
