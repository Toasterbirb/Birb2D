#include "Vector.hpp"
#include "Utils.hpp"

namespace Birb
{
	Vector3::Vector3()
	:x(0.0f), y(0.0f), z(0.0f)
	{}

	Vector3::Vector3(const float& x, const float& y, const float& z)
	:x(x), y(y), z(z)
	{}

	Vector3::Vector3(const float values[3])
	:x(values[0]),y(values[1]), z(values[2])
	{}

	Vector3::Vector3(const Vector2& vec2)
	:x(vec2.x), y(vec2.y), z(0)
	{}

    std::string Vector3::ToString() const
	{
        return "(" + utils::CleanDecimals(x) + ", " + utils::CleanDecimals(y) + ", " + utils::CleanDecimals(z) + ")";
    }

	Vector3Int Vector3::ToInt() const
	{
		return Vector3Int(std::round(x), std::round(y), std::round(z));
	}

    float Vector3::magnitude() const
    {
        return std::sqrt((x * x) + (y * y) + (z * z));
    }

    Vector3 Vector3::normalized() const
    {
        return *this / magnitude();
    }

    void Vector3::Normalize()
    {
        *this = normalized();
    }

    Vector3 Vector3::One()
    {
        return Vector3(1.0f,1.0f,1.0f);
    }

    Vector3 Vector3::Zero()
    {
        return Vector3(0.0f,0.0f,0.0f);
    }

    Vector3 Vector3::Forward()
    {
        return Vector3(0.0f,0.0f,1.0f);
    }

    Vector3 Vector3::Back()
    {
        return Vector3(0.0f,0.0f,-1.0f);
    }

    Vector3 Vector3::Up()
    {
        return Vector3(0.0f,1.0f,0.0f);
    }

    Vector3 Vector3::Down()
    {
        return Vector3(0.0f,-1.0f,0.0f);
    }

    Vector3 Vector3::Left()
    {
        return Vector3(-1.0f,0.0f,0.0f);
    }

    Vector3 Vector3::Right()
    {
        return Vector3(1.0f,0.0f,0.0f);
    }
}
