/* Proposed WG14 improved string support
(C) 2025 Niall Douglas <http://www.nedproductions.biz/>
File Created: Jun 2025


Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License in the accompanying file
Licence.txt or at

http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef WG14_STRING_CONFIG_H
#define WG14_STRING_CONFIG_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#ifndef WG14_STRING_PREFIX
#define WG14_STRING_PREFIX(x) x
#endif

#ifndef WG14_STRING_INLINE
#define WG14_STRING_INLINE inline
#endif

#ifndef WG14_STRING_IF_LIKELY
#if __GNUC__
#define WG14_STRING_IF_LIKELY(expr) if(__builtin_expect(!!(expr), 1))
#elif __STDC_VERSION__ >= 202300L
#define WG14_STRING_IF_LIKELY(expr) if(expr) [[likely]]
#else
#define WG14_STRING_IF_LIKELY(expr) if(expr)
#endif
#endif

#ifndef WG14_STRING_NULLPTR
#if __STDC_VERSION__ >= 202300L
#define WG14_STRING_NULLPTR nullptr
#else
#define WG14_STRING_NULLPTR NULL
#endif
#endif

#ifndef WG14_STRING_DEFAULT_VISIBILITY
#ifdef _WIN32
#define WG14_STRING_DEFAULT_VISIBILITY
#else
#define WG14_STRING_DEFAULT_VISIBILITY __attribute__((visibility("default")))
#endif
#endif

#ifndef WG14_STRING_EXTERN
#if WG14_STRING_SOURCE
#ifdef _WIN32
#define WG14_STRING_EXTERN extern __declspec(dllexport)
#else
#define WG14_STRING_EXTERN extern __attribute__((visibility("default")))
#endif
#else
#define WG14_STRING_EXTERN extern
#endif
#endif

#ifndef WG14_STRING_STDERR_PRINTF
#include <stdio.h>
#define WG14_STRING_STDERR_PRINTF(...) fprintf(stderr, __VA_ARGS__)
#endif

#ifdef __cplusplus
extern "C"
{
#endif

#ifndef WG14_STRING_HAVE_CHAR8_T
  typedef uint8_t char8_t;
#endif

  typedef struct WG14_STRING_PREFIX(varuint8_t) WG14_STRING_PREFIX(varuint8_t);

  //! \brief Returns the number of header octets needed for a given array length
  //! Returns `MAX_SIZE' if the length is too long for a `varuint8_t`.
  static WG14_STRING_INLINE size_t
  WG14_STRING_PREFIX(varuint8_header_size)(size_t arraylen)
  {
    if(arraylen < 8)
    {
      return 1;
    }
    if(arraylen < 72)
    {
      return 2;
    }
    if(arraylen < 262216)
    {
      return 4;
    }
    if(arraylen < 4398046773319ULL)
    {
      return 8;
    }
    return (size_t) -1;
  }

  //! \brief If `datalen` would fit inside `buflen`, place the appropriate
  //! length of header prefix at `buf` and then `data` following. Otherwise
  //! return nullptr.
  WG14_STRING_EXTERN WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_fill)(void *buf, size_t buflen,
                                    const uint8_t *data, size_t datalen);

  //! \brief Convenience alternative for `varuint8_fill()`.
  static WG14_STRING_INLINE WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_fill_ntbs)(void *buf, size_t buflen,
                                         const char *str)
  {
    return WG14_STRING_PREFIX(varuint8_fill)(buf, buflen, (const uint8_t *) str,
                                             strlen(str) + 1);
  }

  //! \brief Dynamically memory allocate the correct number of bytes to
  //! store `datalen` items in the array, and copy `data` into that array.
  //! You must call `free()` on the returned pointer when done with it.
  WG14_STRING_EXTERN WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_malloc)(const uint8_t *data, size_t datalen);

  //! \brief Convenience alternative for `varuint8_malloc()`.
  static WG14_STRING_INLINE WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_malloc_ntbs)(const char *str)
  {
    return WG14_STRING_PREFIX(varuint8_malloc)((const uint8_t *) str,
                                               strlen(str) + 1);
  }

  //! \brief Concatenate multiple `varuint8_t'
  WG14_STRING_EXTERN WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_cat_N)(
  void *buf, size_t buflen, const WG14_STRING_PREFIX(varuint8_t) *const *arrs,
  size_t arrslen);

  //! \brief Concatenate two `varuint8_t'
  static WG14_STRING_INLINE WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_cat)(void *buf, size_t buflen,
                                   const WG14_STRING_PREFIX(varuint8_t) * arr1,
                                   const WG14_STRING_PREFIX(varuint8_t) * arr2)
  {
    const WG14_STRING_PREFIX(varuint8_t) *const arrs[2] = {arr1, arr2};
    return WG14_STRING_PREFIX(varuint8_cat_N)(buf, buflen, arrs, 2);
  }

  //! \brief Dynamically memory allocate a clone of the `varuint8_t'.
  //! You must call `free()` on the returned pointer when done with it.
  WG14_STRING_EXTERN WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_dup)(const WG14_STRING_PREFIX(varuint8_t) * arr);


  //! \brief Returns the size of the array for access i.e. elements in the
  //! array.
  WG14_STRING_EXTERN size_t WG14_STRING_PREFIX(varuint8_length)(
  const WG14_STRING_PREFIX(varuint8_t) * arr);

  //! \brief Returns the size of the array for memory copying i.e. including
  //! header bytes.
  WG14_STRING_EXTERN size_t WG14_STRING_PREFIX(varuint8_sizeof)(
  const WG14_STRING_PREFIX(varuint8_t) * arr);

  //! \brief Return a pointer to the uint8_t at the beginning of the array
  //! Returns nullptr if array is zero length.
  WG14_STRING_EXTERN uint8_t *
  WG14_STRING_PREFIX(varuint8_front)(WG14_STRING_PREFIX(varuint8_t) * arr);

  //! \brief Return a pointer to the uint8_t at the end of the array
  //! Returns nullptr if array is zero length.
  WG14_STRING_EXTERN uint8_t *
  WG14_STRING_PREFIX(varuint8_back)(WG14_STRING_PREFIX(varuint8_t) * arr);

  //! \brief Return a pointer to the uint8_t just after the end of the array.
  //! Useful for iteration between front and end.
  //! Returns nullptr if array is zero length to match front.
  static WG14_STRING_INLINE uint8_t *
  WG14_STRING_PREFIX(varuint8_end)(WG14_STRING_PREFIX(varuint8_t) * arr)
  {
    uint8_t *back = WG14_STRING_PREFIX(varuint8_back)(arr);
    if(back == WG14_STRING_NULLPTR)
    {
      return WG14_STRING_NULLPTR;
    }
    return back + 1;
  }

  //! \brief Return a pointer to the uint8_t at idx into the array
  //! Returns nullptr if idx is outside array.
  WG14_STRING_EXTERN uint8_t *
  WG14_STRING_PREFIX(varuint8_index)(WG14_STRING_PREFIX(varuint8_t) * arr,
                                     size_t idx);

  //! \brief Return a NTBS if array is null terminated AND contains
  //! no intermediate null values, nullptr otherwise. Obviously this implies
  //! a O(N) complexity. No checking that the array is valid UTF-8 is done.
  WG14_STRING_EXTERN char8_t *
  WG14_STRING_PREFIX(ntbs_from_varuint8)(WG14_STRING_PREFIX(varuint8_t) * arr);

  //! \brief Return a pointer to the `char8_t` at or preceding arr[idx]
  //! Returns nullptr if idx is outside array or there is no
  //! structurally valid UTF-8 codepoint at that index
  WG14_STRING_EXTERN char8_t *WG14_STRING_PREFIX(char8_from_varuint8_index)(
  WG14_STRING_PREFIX(varuint8_t) * arr, size_t idx);

  //! \brief Copy a `varuint8_t' into a user supplied buffer.
  static WG14_STRING_INLINE WG14_STRING_PREFIX(varuint8_t) *
  WG14_STRING_PREFIX(varuint8_cpy)(void *buf, size_t buflen,
                                   const WG14_STRING_PREFIX(varuint8_t) * arr)
  {
    const size_t length = WG14_STRING_PREFIX(varuint8_length)(arr);
    return WG14_STRING_PREFIX(varuint8_fill)(
    buf, buflen,
    (length > 0) ?
    WG14_STRING_PREFIX(varuint8_front)((WG14_STRING_PREFIX(varuint8_t) *) arr) :
    WG14_STRING_NULLPTR,
    length);
  }


#ifdef __cplusplus
}
#endif

#endif
