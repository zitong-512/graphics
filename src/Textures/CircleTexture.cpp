#include "Textures/CircleTexture.hpp"
#include <cmath>
#include <stdexcept>

CircleTexture::CircleTexture(Vec3 color0,
                                         Vec3 color1,
                                         Vec3 color2,
                                         Vec3 color3,
                                         Vec3 color4,
                                         Vec3 color5,
                                         Vec3 color6,
                                         Vec3 color7,
                                         float radius,
                                        Vec2 center)
    : color0_(color0),
      color1_(color1),
      color2_(color2),
      color3_(color3),
      color4_(color4),
      color5_(color5),
      color6_(color6),
      color7_(color7),
      radius_(radius),
      center_(center) {
    if (radius_ <= 0.0f) {
        throw std::invalid_argument(
            "Circle texture tile size must be positive"
        );
    }
} 

Vec3 CircleTexture::sample(const Vec2& uv) const {
    float dx = uv.x - center_.x;
    float dy = uv.y - center_.y;
    int distance = static_cast<int>(std::round(sqrt(dx * dx + dy * dy)));   
    if ((distance) % 8 == 0) {
        return color7_;
    } else if ((distance) % 7 == 0) {
        return color6_;
    } else if ((distance) % 7 == 1) {
        return color5_;
    } else if ((distance) % 7 == 2) {
        return color4_;
    } else if ((distance) % 7 == 3) {
        return color3_;
    } else if ((distance) % 7 == 4) {
        return color2_;
    } else if ((distance) % 7 == 5) {
        return color1_;
    } else {
        return color0_;
    }
                                           
}                                   

                                                                                                                                                                                  

 
                                                                                

                                                                                                                        