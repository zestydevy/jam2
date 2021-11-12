
#pragma once

#include <nusys.h>

// -------------------------------------------------------------------------- //

float constexpr kFrameRate = 60.0f;
float constexpr kInterval = 1.0f / kFrameRate;

// -------------------------------------------------------------------------- //

class TUtil
{
    public:

    static void toMemory(void * dest, void * src, s32 size);
    static f32 getTick(){return sGameTick;}
    static void setTick(float const tick){sGameTick = tick;}
    static void tick(){++sGameTick;}

    protected:
    
    static float sGameTick;
};

// -------------------------------------------------------------------------- //

class TTimer {

  public:

  TTimer() = default;
  ~TTimer() = default;

  void start(float seconds);
  bool update(); // returns true if 0

  // returns float seconds
  float get(
    u32 * min = nullptr,
    u32 * sec = nullptr,
    u32 * ms = nullptr
  ) const;

  private:

  float mTime { 0.0F };

};

// -------------------------------------------------------------------------- //
