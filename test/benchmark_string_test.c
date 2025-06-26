#include "test_common.h"

#include "ticks_clock.h"

int main(void)
{
  int ret = 0;
  puts("Preparing benchmark ...");
  cpu_ticks_count get_ticks_count_overhead = (cpu_ticks_count) -1;
  {
    const ns_count begin = get_ns_count();
    ns_count end = begin;
    cpu_ticks_count ticks = 0, ops = 0;
    do
    {
      cpu_ticks_count s = get_ticks_count(memory_order_relaxed);
      cpu_ticks_count e = get_ticks_count(memory_order_relaxed);
      ticks += e - s;
      ops++;
    } while(end = get_ns_count(), end - begin < 1000000000);
    get_ticks_count_overhead =
    (cpu_ticks_count) ((double) ticks / (double) ops);
  }
  const cpu_ticks_count ticks_per_sec = ticks_per_second();
  printf("There are %llu ticks per second and get_ticks_count_overhead=%llu.\n",
         (unsigned long long) ticks_per_sec,
         (unsigned long long) get_ticks_count_overhead);
  puts("Running benchmark ...");
  char buffer[16];
  {
    const ns_count begin = get_ns_count();
    ns_count end = begin;
    cpu_ticks_count ticks = 0, ops = 0;
    do
    {
      cpu_ticks_count s = get_ticks_count(memory_order_relaxed);
      for(size_t n = 0; n < 65536; n++)
      {
        volatile WG14_STRING_PREFIX(varuint8_t) *val = WG14_STRING_PREFIX(
        varuint8_fill)(buffer, sizeof(buffer), (const uint8_t *) "", 0);
        (void) val;
      }
      cpu_ticks_count e = get_ticks_count(memory_order_relaxed);
      ticks += e - s - get_ticks_count_overhead;
      ops += 65536;
    } while(end = get_ns_count(), end - begin < 3000000000);
    printf("\nOn this platform varuint8_fill() "
           "takes %f nanoseconds.\n\n",
           (double) ticks / ((double) ticks_per_sec / 1000000000.0) /
           (double) ops);
  }
  WG14_STRING_PREFIX(varuint8_t) *arr = WG14_STRING_PREFIX(varuint8_fill)(
  buffer, sizeof(buffer), (const uint8_t *) "niall", 6);
  {
    const ns_count begin = get_ns_count();
    ns_count end = begin;
    cpu_ticks_count ticks = 0, ops = 0;
    do
    {
      cpu_ticks_count s = get_ticks_count(memory_order_relaxed);
      for(size_t n = 0; n < 65536; n++)
      {
        volatile size_t val = WG14_STRING_PREFIX(varuint8_length)(arr);
        (void) val;
      }
      cpu_ticks_count e = get_ticks_count(memory_order_relaxed);
      ticks += e - s - get_ticks_count_overhead;
      ops += 65536;
    } while(end = get_ns_count(), end - begin < 3000000000);
    printf("\nOn this platform varuint8_length() "
           "takes %f nanoseconds.\n\n",
           (double) ticks / ((double) ticks_per_sec / 1000000000.0) /
           (double) ops);
  }
  {
    const ns_count begin = get_ns_count();
    ns_count end = begin;
    cpu_ticks_count ticks = 0, ops = 0;
    do
    {
      cpu_ticks_count s = get_ticks_count(memory_order_relaxed);
      for(size_t n = 0; n < 65536; n++)
      {
        volatile uint8_t *val = WG14_STRING_PREFIX(varuint8_index)(arr, 3);
        (void) val;
      }
      cpu_ticks_count e = get_ticks_count(memory_order_relaxed);
      ticks += e - s - get_ticks_count_overhead;
      ops += 65536;
    } while(end = get_ns_count(), end - begin < 3000000000);
    printf("\nOn this platform varuint8_index() "
           "takes %f nanoseconds.\n\n",
           (double) ticks / ((double) ticks_per_sec / 1000000000.0) /
           (double) ops);
  }
  printf("Exiting main with result %d ...\n", ret);
  return ret;
}
