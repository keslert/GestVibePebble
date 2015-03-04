#include <pebble.h>
#include "vibrations.h"

static VibePattern patterns[10]; 

static const uint32_t p0[] = { 100 };
static const uint32_t p1[] = { 100, 150, 100 };
static const uint32_t p2[] = { 100, 150, 100, 150, 100 };
static const uint32_t p3[] = { 100, 150, 100, 150, 100, 150, 100 };
static const uint32_t p4[] = { 500 };
static const uint32_t p5[] = { 500, 150, 100 };
static const uint32_t p6[] = { 500, 150, 100, 150, 100 };
static const uint32_t p7[] = { 500, 150, 100, 150, 100, 150, 100 };
static const uint32_t p8[] = { 500, 150, 100, 150, 100, 150, 100, 150, 100 };
static const uint32_t p9[] = { 500, 150, 500 };

void init_vibrations() {
  patterns[0].durations = p0;
  patterns[0].num_segments = ARRAY_LENGTH(p0);
  patterns[1].durations = p1;
  patterns[1].num_segments = ARRAY_LENGTH(p1);
  patterns[2].durations = p2;
  patterns[2].num_segments = ARRAY_LENGTH(p2);
  patterns[3].durations = p3;
  patterns[3].num_segments = ARRAY_LENGTH(p3);
  patterns[4].durations = p4;
  patterns[4].num_segments = ARRAY_LENGTH(p4);
  patterns[5].durations = p5;
  patterns[5].num_segments = ARRAY_LENGTH(p5);
  patterns[6].durations = p6;
  patterns[6].num_segments = ARRAY_LENGTH(p6);
  patterns[7].durations = p7;
  patterns[7].num_segments = ARRAY_LENGTH(p7);
  patterns[8].durations = p8;
  patterns[8].num_segments = ARRAY_LENGTH(p8);
  patterns[9].durations = p9;
  patterns[9].num_segments = ARRAY_LENGTH(p9);
}

void play_pattern(int pattern)
{
  vibes_enqueue_custom_pattern(patterns[pattern - 1]);
}