#include <pebble.h>
#include "vibrations.h"

static VibePattern patterns[10];
static VibePattern transitions[2];

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

// Transition between two different vibrations
static const uint32_t t0[] = { 350, 100, 50, 100, 50, 100, 50, 100, 350 };
static const uint32_t t1[] = { 1500 };

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
  
  transitions[0].durations = t0;
  transitions[0].num_segments = ARRAY_LENGTH(t0);
  transitions[1].durations = t1;
  transitions[1].num_segments = ARRAY_LENGTH(t1);
}

void play_pattern(int pattern)
{
  if(pattern <= 10) {
    vibes_enqueue_custom_pattern(patterns[pattern - 1]);
  } else {
    int p1 = pattern / 100;
    int p2 = pattern % 100;
    
    VibePattern vp1 = patterns[p1 - 1];
    VibePattern vp2 = patterns[p2 - 1];
    VibePattern t = transitions[1];
    
    uint32_t* combined = malloc((vp1.num_segments + vp2.num_segments + t.num_segments) * sizeof(uint32_t)); // array to hold the result

    memcpy(combined,                                      vp1.durations, vp1.num_segments * sizeof(uint32_t)); 
    memcpy(combined + vp1.num_segments,                   t.durations,   t.num_segments * sizeof(uint32_t)); 
    memcpy(combined + vp1.num_segments + t.num_segments,  vp2.durations, vp2.num_segments * sizeof(uint32_t));
    
    VibePattern p = {
      .durations = combined,
      .num_segments = vp1.num_segments + vp2.num_segments + t.num_segments
    };
    
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Combining resulted in: %d", (int)(vp1.num_segments + vp2.num_segments + t.num_segments)); 
    
    vibes_enqueue_custom_pattern(p);
    
//     vibes_enqueue_custom_pattern(patterns[p1  - 1]);
//     vibes_enqueue_custom_pattern(transitions[0]);
//     vibes_enqueue_custom_pattern(patterns[p2  - 1]);
  }
}