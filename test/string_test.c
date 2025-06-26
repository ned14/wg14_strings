#include "test_common.h"

int main(void)
{
  int ret = 0;
  {
    static const char teststring[] = "Hello";
    WG14_STRING_PREFIX(varuint8_t) *arr =
    WG14_STRING_PREFIX(varuint8_malloc_ntbs)(teststring);
    CHECK(WG14_STRING_PREFIX(varuint8_length)(arr) == 6);
    CHECK(WG14_STRING_PREFIX(varuint8_sizeof)(arr) == 7);
    CHECK(WG14_STRING_PREFIX(varuint8_back)(arr) -
          WG14_STRING_PREFIX(varuint8_front)(arr) ==
          5);
    CHECK(*WG14_STRING_PREFIX(varuint8_index)(arr, 4) == 'o');
    CHECK(*WG14_STRING_PREFIX(varuint8_back)(arr) == 0);
    CHECK(0 == strcmp(teststring,
                      (char *) WG14_STRING_PREFIX(ntbs_from_varuint8)(arr)));
    free(arr);
  }
  {
    static const char teststring[] = "Hello, I am a teapot!";
    WG14_STRING_PREFIX(varuint8_t) *arr =
    WG14_STRING_PREFIX(varuint8_malloc_ntbs)(teststring);
    CHECK(WG14_STRING_PREFIX(varuint8_length)(arr) == 22);
    CHECK(WG14_STRING_PREFIX(varuint8_sizeof)(arr) == 24);
    CHECK(WG14_STRING_PREFIX(varuint8_back)(arr) -
          WG14_STRING_PREFIX(varuint8_front)(arr) ==
          21);
    CHECK(*WG14_STRING_PREFIX(varuint8_index)(arr, 4) == 'o');
    CHECK(*WG14_STRING_PREFIX(varuint8_back)(arr) == 0);
    CHECK(0 == strcmp(teststring,
                      (char *) WG14_STRING_PREFIX(ntbs_from_varuint8)(arr)));
    free(arr);
  }
  {
    static const char teststring[] = "Hello, I am a teapot! Short and stout. "
                                     "Lift me up, and pour me out. Goodbye";
    WG14_STRING_PREFIX(varuint8_t) *arr =
    WG14_STRING_PREFIX(varuint8_malloc_ntbs)(teststring);
    CHECK(WG14_STRING_PREFIX(varuint8_length)(arr) == 76);
    CHECK(WG14_STRING_PREFIX(varuint8_sizeof)(arr) == 80);
    CHECK(WG14_STRING_PREFIX(varuint8_back)(arr) -
          WG14_STRING_PREFIX(varuint8_front)(arr) ==
          75);
    CHECK(*WG14_STRING_PREFIX(varuint8_index)(arr, 4) == 'o');
    CHECK(*WG14_STRING_PREFIX(varuint8_back)(arr) == 0);
    CHECK(0 == strcmp(teststring,
                      (char *) WG14_STRING_PREFIX(ntbs_from_varuint8)(arr)));
    free(arr);
  }
  printf("Exiting main with result %d ...\n", ret);
  return ret;
}
