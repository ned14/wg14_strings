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

#ifndef WG14_STRING_PREFIX
#define WG14_STRING_PREFIX(x) x
#endif

#ifndef WG14_STRING_INLINE
#define WG14_STRING_INLINE inline
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

  // Returns the size of the array for access
  WG14_STRING_EXTERN size_t WG14_STRING_PREFIX(varuint8_length)(
  const WG14_STRING_PREFIX(varuint8_t) * arr);

  // Returns the size of the array for memory copying
  WG14_STRING_EXTERN size_t WG14_STRING_PREFIX(varuint8_sizeof)(
  const WG14_STRING_PREFIX(varuint8_t) * arr);

  // Return a pointer to the uint8_t at the beginning of the array
  // Returns nullptr if array is zero length
  WG14_STRING_EXTERN uint8_t *
  WG14_STRING_PREFIX(varuint8_front)(WG14_STRING_PREFIX(varuint8_t) * arr);

  // Return a pointer to the uint8_t at the end of the array
  // Returns nullptr if array is zero length
  WG14_STRING_EXTERN uint8_t *
  WG14_STRING_PREFIX(varuint8_back)(WG14_STRING_PREFIX(varuint8_t) * arr);

  // Return a pointer to the uint8_t at idx into the array
  // Returns nullptr if idx is outside array
  WG14_STRING_EXTERN uint8_t *
  WG14_STRING_PREFIX(varuint8_index)(WG14_STRING_PREFIX(varuint8_t) * arr,
                                     size_t idx);

  // Return a NTBS if array is null terminated AND contains
  // no intermediate null values, nullptr otherwise
  WG14_STRING_EXTERN char8_t *
  WG14_STRING_PREFIX(ntbs_from_varuint8)(WG14_STRING_PREFIX(varuint8_t) * arr);

  // Return a pointer to the char8_t at or preceding arr[idx]
  // Returns nullptr if idx is outside array or there is no
  // valid UTF-8 codepoint at that index
  WG14_STRING_EXTERN char8_t *WG14_STRING_PREFIX(char8_from_varuint8_index)(
  WG14_STRING_PREFIX(varuint8_t) * arr, size_t idx);

#ifdef __cplusplus
}
#endif

#endif
