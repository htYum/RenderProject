#ifndef MYMATH_H
#define MYMATH_H

#include <cmath>

class vec2
{
public:
    float x, y;

    vec2() = default;
    ~vec2() = default;
    vec2(float newX, float newY):x(newX),y(newY){}
    vec2(const vec2& vec):x(vec.x),y(vec.y){}
    vec2(float val):x(val), y(val){}

    void setX(float newX){x = newX;}
    void setY(float newY){y = newY;}
    void set(float newX, float newY){x = newX;y = newY;}
    float getX(){return x;}
    float getY(){return y;}

    vec2 operator+(const vec2& rhs)const {return vec2(x+rhs.x, y+rhs.y);}
    vec2 operator-(const vec2& rhs)const {return vec2(x-rhs.x, y-rhs.y);}
    vec2 operator*(const float rhs)const {return vec2(x*rhs, y*rhs);}
    vec2 operator/(const float rhs)const {return (rhs == 0)? vec2(0.0f, 0.0f):vec2(x/rhs, y/rhs);}
    vec2 operator=(const vec2& rhs) {x = rhs.x;y = rhs.y;return *this;}

    bool operator==(const vec2& rhs)const {return (x == rhs.x)&&(y == rhs.y);}
    bool operator!=(const vec2& rhs)const {return !(*this == rhs);}

    void operator+=(const vec2& rhs){x+=rhs.x;y+=rhs.y;}
    void operator-=(const vec2& rhs){x-=rhs.x;y-=rhs.y;}
    void operator*=(const float rhs){x*=rhs;y*=rhs;}
    void operator/=(const float rhs){if(rhs!=0){x/=rhs;y/=rhs;}}

    vec2 operator-()const {return vec2(-x, -y);}
};

class vec3
{
public:
    float x,y,z;

    vec3() = default;
    ~vec3() = default;
    vec3(float newX, float newY, float newZ):x(newX), y(newY), z(newZ){}
    vec3(const vec3& vec):x(vec.x), y(vec.y), z(vec.z){}
    vec3(float val):x(val), y(val), z(val){}

    void setX(float newX){x = newX;}
    void setY(float newY){y = newY;}
    void setZ(float newZ){z = newZ;}
    void set(float newX, float newY, float newZ){x = newX;y = newY;z = newZ;}
    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}

    vec3 operator+(const vec3& rhs)const {return vec3(x+rhs.x, y+rhs.y, z+rhs.z);}
    vec3 operator-(const vec3& rhs)const {return vec3(x-rhs.x, y-rhs.y, z-rhs.z);}
    vec3 operator*(const float rhs)const {return vec3(x*rhs, y*rhs, z*rhs);}
    vec3 operator/(const float rhs)const {return (rhs == 0)? vec3(0.0f, 0.0f, 0.0f):vec3(x/rhs, y/rhs, z/rhs);}
    vec3 operator=(const vec3& rhs) {x = rhs.x;y = rhs.y;z = rhs.z;return *this;}

    bool operator==(const vec3& rhs)const {return (x == rhs.x)&&(y == rhs.y)&&(z == rhs.z);}
    bool operator!=(const vec3& rhs)const {return !(*this == rhs);}

    void operator+=(const vec3& rhs){x+=rhs.x;y+=rhs.y;z+=rhs.z;}
    void operator-=(const vec3& rhs){x-=rhs.x;y-=rhs.y;z-=rhs.z;}
    void operator*=(const float rhs){x*=rhs;y*=rhs;z*=rhs;}
    void operator/=(const float rhs){if(rhs!=0){x/=rhs;y/=rhs;z/=rhs;}}

    vec3 operator-()const {return vec3(-x, -y, -z);}
};

class vec4
{
public:
    float x,y,z,w;

    vec4() = default;
    ~vec4() = default;
    vec4(float newX, float newY, float newZ, float newW):x(newX),y(newY),z(newZ),w(newW){}
    vec4(const vec4& vec):x(vec.x),y(vec.y),z(vec.z),w(vec.w){}
    vec4(float val):x(val), y(val), z(val), w(val){}
    vec4(const vec3& vec, float val):x(vec.x),y(vec.y),z(vec.z),w(val){}
    vec4(const vec3& vec):x(vec.x),y(vec.y),z(vec.z),w(1.0f){}
    vec4(float val, const vec3& vec):x(val),y(vec.x),z(vec.y),w(vec.z){}

    void setX(float newX){x = newX;}
    void setY(float newY){y = newY;}
    void setZ(float newZ){z = newZ;}
    void setW(float newW){w = newW;}
    void set(float newX, float newY, float newZ, float newW){x = newX;y = newY;z = newZ;w = newW;}
    void set(float val, const vec3& vec){x = val;y = vec.x;z = vec.y;w = vec.z;}
    void set(const vec3& vec, float val){x = vec.x;y = vec.y;z = vec.z;w = val;}
    float getX(){return x;}
    float getY(){return y;}
    float getZ(){return z;}
    float getW(){return w;}

    vec4 operator+(const vec4& rhs)const {return vec4(x+rhs.x, y+rhs.y, z+rhs.z, w+rhs.w);}
    vec4 operator-(const vec4& rhs)const {return vec4(x-rhs.x, y-rhs.y, z-rhs.z, w-rhs.w);}
    vec4 operator*(const float rhs)const {return vec4(x*rhs, y*rhs, z*rhs, w*rhs);}
    vec4 operator/(const float rhs)const {return (rhs == 0)? vec4(0.0f, 0.0f, 0.0f, 0.0f):vec4(x/rhs, y/rhs, z/rhs, w/rhs);}
    vec4 operator=(const vec4& rhs) {x = rhs.x;y = rhs.y;z = rhs.z;w = rhs.w;return *this;}

    bool operator==(const vec4& rhs)const {return (x == rhs.x)&&(y == rhs.y)&&(z == rhs.z)&&(w == rhs.w);}
    bool operator!=(const vec4& rhs)const {return !(*this == rhs);}

    void operator+=(const vec4& rhs){x+=rhs.x;y+=rhs.y;z+=rhs.z;w+=rhs.w;}
    void operator-=(const vec4& rhs){x-=rhs.x;y-=rhs.y;z-=rhs.z;w-=rhs.w;}
    void operator*=(const float rhs){x*=rhs;y*=rhs;z*=rhs;w*=rhs;}
    void operator/=(const float rhs){if(rhs!=0){x/=rhs;y/=rhs;z/=rhs;w/=rhs;}}

    vec4 operator-()const {return vec4(-x, -y, -z, -w);}
};

inline float dot(const vec2& lhs, const vec2& rhs);
inline float dot(const vec3& lhs, const vec3& rhs);
inline float dot(const vec4& lhs, const vec4& rhs);

inline vec3 cross(const vec3& lhs, const vec3& rhs);

template<class T>
inline T normalize(T vec);

template<class T>
inline float length(T vec);

class mat4x4
{
public:
    vec4 value[4] = {vec4(1.0f,0,0,0),vec4(0,1.0f,0,0),vec4(0,0,1.0f,0),vec4(0,0,0,1.0f)};  // colume
    mat4x4();
    ~mat4x4() = default;
    mat4x4(const vec4& vec):
        value{vec,vec,vec,vec}{}
    mat4x4(const vec4& v1,
           const vec4& v2,
           const vec4& v3,
           const vec4& v4):
        value{v1,v2,v3,v4}{}
    mat4x4(const float& f1,const float& f2,const float& f3,const float& f4,
           const float& f5,const float& f6,const float& f7,const float& f8,
           const float& f9,const float& f10,const float& f11,const float& f12,
           const float& f13,const float& f14,const float& f15,const float& f16):
        value{vec4(f1,f2,f3,f4),vec4(f5,f6,f7,f8),vec4(f9,f10,f11,f12),vec4(f13,f14,f15,f16)}{}

    mat4x4 operator+(const mat4x4& rhs) const;
    mat4x4 operator-(const mat4x4& rhs) const;
    mat4x4 operator*(const float& rhs) const;
    mat4x4 operator/(const float& rhs) const;
    mat4x4 operator*(const mat4x4& rhs) const;
    vec4 operator*(const vec4& rhs) const;

    bool operator==(const mat4x4& rhs) const;
    bool operator!=(const mat4x4& rhs) const;

    mat4x4 operator-() const;

};

mat4x4 getViewPortMatrix(int x, int y, int width, int height);

vec2 lerp(const vec2& a,const vec2& b,float factor);
vec3 lerp(const vec3& a,const vec3& b,float factor);
vec4 lerp(const vec4& a,const vec4& b,float factor);

#endif // MYMATH_H
