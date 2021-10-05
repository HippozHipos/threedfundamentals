#pragma once
#include "Eigen.h"

class Rotation
{
public:
	template<typename T>
	static Eigen::Matrix<T, 3, 3> Roll(T angle) noexcept
	{
		return [&] {
			Eigen::Matrix<T, 3, 3> temp;
			const T sinTheta = std::sin(angle);
			const T cosTheta = std::cos(angle);
			temp << 
				cosTheta, -sinTheta, (T)0.0f,
			    sinTheta,  cosTheta, (T)0.0f,
				(T)0.0f,  (T)0.0f,  (T)1.0f;
			return temp;
		}();
	}

	template<typename T>
	static Eigen::Matrix<T, 3, 3> Pitch(T angle) noexcept
	{
		return [&] {
			Eigen::Matrix<T, 3, 3> temp;
			const T sinTheta = std::sin(angle);
			const T cosTheta = std::cos(angle);
			temp <<
				(T)1.0f,   (T)0.0f,  (T)0.0f,
				(T)0.0f,   cosTheta, -sinTheta,
				(T)0.0f,  sinTheta, cosTheta;
			return temp;
		}();
	}

	template<typename T>
	static Eigen::Matrix<T, 3, 3> Yaw(T angle) noexcept
	{
		return [&] {
			Eigen::Matrix<T, 3, 3> temp;
			const T sinTheta = std::sin(angle);
			const T cosTheta = std::cos(angle);
			temp <<
				 cosTheta,  (T)0.0f,   sinTheta,
				 (T)0.0f,   (T)1.0f,   (T)0.0f,
				-sinTheta,  (T)0.0f,   cosTheta;
			return temp;
		}();
	}

	template<typename T>
	static Eigen::Matrix<T, 3, 1> Rotate(const Eigen::Matrix<T, 3, 1>& v, T roll, T pitch, T yaw) noexcept
	{
		auto wrap = [](float& angle)
		{
			if (angle > 3.141592653589793238462643f)
				angle -= 3.141592653589793238462643f * 2.0f;

			if (angle < -3.141592653589793238462643f)
				angle += 3.141592653589793238462643f * 2.0f;

		};

		wrap(roll);
		wrap(pitch);
		wrap(yaw);
		return (Roll(roll) * Pitch(pitch) * Yaw(yaw)) * v;
	}
};

