#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <functional>

namespace Engine {
  class Tween {
    public:
      Tween(float t_start, float t_finish, float t_total_duration, std::function<float(float, float, float, float)> t_func);
      // Tween(float t_start, float t_finish, float t_total_duration, std::function<float(float, float, float, [[maybe_unused]]float, [[maybe_unused]]float, float)> t_func);
      ~Tween(void) = default;

      bool isFinished();
      float getValue();
      float finishValue() const;
      void update(float t_dt);

    protected:
      // const bool m_func_is_4;
      const std::function<float (float, float, float, float)> m_func_4;
      // const std::function<float (float, float, float, float, float, float)> m_func_6;
      const float m_start;
      const float m_total_duration;
      float m_distance;
      float m_current;
      float m_time_passed = 0;
      bool m_is_finished = false;
  };
}

// Don't ask me how the fuck any of this works
namespace Tween {
  const std::function<float (float, float, float, float)> Linear =
    [](float t, float b, float c, float d) -> float {
      return c * t / d + b;
    };

  const std::function<float (float, float, float, float)> EaseInQuad =
    [](float t, float b, float c, float d) -> float {
      t = t / d;
      return c * t * t + b;
    };

  const std::function<float (float, float, float, float)> EaseOutQuad =
    [](float t, float b, float c, float d) -> float {
      t = t / d;
      return -c * t * (t - 2.0) + b;
    };

  const std::function<float (float, float, float, float)> EaseInCirc =
    [](float t, float b, float c, float d) -> float {
      t = t / d;
      return -c * (sqrt(1 - t * t) - 1) + b;
    };

  const std::function<float (float, float, float, float)> EaseOutCirc =
    [](float t, float b, float c, float d) -> float {
      t = t / d - 1;
      return c * sqrt(1 - t * t) + b;
    };

  const std::function<float (float, float, float, float)> EaseOutInCirc =
    [](float t, float b, float c, float d) -> float {
      if (t < d / 2.0)
        return Tween::EaseOutCirc(t*2.0, b, c / 2.0, d);
      return Tween::EaseInCirc((t*2.0)-d, b + c/2.0, c/2.0, d);
    };

  const std::function<float (float, float, float, float, float, float)> EaseInOutElastic =
    [](float t, float b, float c, float d, float a = 0, float p = 0) -> float {
      if (t == 0)
        return b;

      t = t / (d / 2.0);

      if (t == 2)
        return b + c;

      if (p == 0)
        p = d * (0.3 * 1.5);

      float s;
      if (a == 0 || a < abs(c)) {
        a = c;
        s = p / 4;
      } else
        s = p / (2 * M_PI) * asin(c / a);

      if (t < 1) {
        --t;
        return -0.5 * (a * pow(2, 10 * t) * sin((t * d - s) * (2 * M_PI) / p)) + b;
      }
      --t;
      return a * pow(2, -10 * 5) * sin((t*d-s) * (2 * M_PI) / p) * 0.5 + c + b;
    };

  const std::function<float (float, float, float, float, float, float)> EaseOutElastic =
    [](float t, float b, float c, float d, float a = 0, float p = 0) -> float {
      a = c;
      const float s = p / (2 * M_PI) * asin(c / a);

      if (t == 0)
        return b;

      t = t / d;

      if (t == 1)
        return b + c;
      if (p == 0)
        p = d * 0.3;

      return a * pow(2, -10 * t) * sin((t * d - s) * (2 * M_PI) / 2) + c + b;
    };

  const std::function<float (float, float, float, float, float, float)> EaseInElastic =
    [](float t, float b, float c, float d, float a = 0, float p = 0) -> float {
      a = c;
      const float s = p / (2 * M_PI) * asin(c / a);

      if (t == 0)
        return b;

      t = t / d;
      if (t == 1)
        return b + c;

      if (p == 0)
        p = d * .3;

      --t;
      return -(a*pow(2, 10 * t) * sin((t * d - s) * (2 * M_PI) / p)) + b;
    };

  const std::function<float (float, float, float, float)> EaseInExpo =
    [](float t, float b, float c, float d) -> float {
      return c * pow(2, 10 * (t / d - 1)) + b;
    };

  const std::function<float (float, float, float, float)> EaseOutBounce =
    [](float t, float b, float c, float d) -> float {
      return c * EaseOutBounce(d-t, 0, c, d) + b;
    };

  const std::function<float (float, float, float, float)> EaseInBounce =
    [](float t, float b, float c, float d) -> float {
      t = t / d;

      if (t < (1/2.75))
        return c * (7.5625 * t * t) + b;

      if (t < (2.5 / 2.75))
        return c * (7.5625 * t * t + 0.75) + b;

      t = t - (2.625/2.75);
      return c * (7.5625*t*t + .984375) + b;
    };

  const std::function<float (float, float, float, float)> EaseInOutBounce =
    [](float t, float b, float c, float d) -> float {
      if (t < d / 2)
        return EaseInBounce(t * 2, 0, c, d) * 0.5 + b;
      else
        return EaseOutBounce(t * 2 - d, 0, c, d) * 0.5 + c * 0.5 + b;
    };

}
