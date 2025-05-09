/*
 * Copyright (C) Yakiv Matiash
 */

#pragma once

#include "pch.h"

namespace cgmath {

struct alignas(8) matrix3x4 {
  union {
    struct {
      float _11, _12, _13, _14;
      float _21, _22, _23, _24;
      float _31, _32, _33, _34;
    } _m;
    float m[3][4];
  };

  matrix3x4() noexcept 
  : _m{0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f} {}

  constexpr matrix3x4(float m00, float m01, float m02, float m03,
                      float m10, float m11, float m12, float m13,
                      float m20, float m21, float m22, float m23) noexcept
  : _m{m00, m01, m02, m03, m10, m11, m12, m13, m20, m21, m22, m23} {}

  explicit matrix3x4(const float* arr) noexcept {
    _m._11 = arr[0]; _m._12 = arr[1]; _m._13 = arr[2]; _m._14 = arr[3];
    _m._21 = arr[4]; _m._22 = arr[5]; _m._23 = arr[6]; _m._24 = arr[7];
    _m._31 = arr[8]; _m._32 = arr[9]; _m._33 = arr[10]; _m._34 = arr[11];
  }

  float operator()(size_t row, size_t col) const noexcept {
    return m[row][col];
  }

  float& operator()(size_t row, size_t col) noexcept {
    return m[row][col];
  }

  constexpr matrix3x4 operator+(const matrix3x4& other) const noexcept {
    return matrix3x4(
      _m._11 + other._m._11, _m._12 + other._m._12, _m._13 + other._m._13, _m._14 + other._m._14,
      _m._21 + other._m._21, _m._22 + other._m._22, _m._23 + other._m._23, _m._24 + other._m._24,
      _m._31 + other._m._31, _m._32 + other._m._32, _m._33 + other._m._33, _m._34 + other._m._34
    );
  }

  constexpr matrix3x4 operator-(const matrix3x4& other) const noexcept {
    return matrix3x4(
      _m._11 - other._m._11, _m._12 - other._m._12, _m._13 - other._m._13, _m._14 - other._m._14,
      _m._21 - other._m._21, _m._22 - other._m._22, _m._23 - other._m._23, _m._24 - other._m._24,
      _m._31 - other._m._31, _m._32 - other._m._32, _m._33 - other._m._33, _m._34 - other._m._34
    );
  }

  constexpr matrix3x4 operator*(float scalar) const noexcept {
    return matrix3x4(
      _m._11 * scalar, _m._12 * scalar, _m._13 * scalar, _m._14 * scalar,
      _m._21 * scalar, _m._22 * scalar, _m._23 * scalar, _m._24 * scalar,
      _m._31 * scalar, _m._32 * scalar, _m._33 * scalar, _m._34 * scalar
    );
  }

  constexpr matrix3x4 transpose() const noexcept {
    return matrix3x4(
      _m._11, _m._21, _m._31,
      _m._12, _m._22, _m._32,
      _m._13, _m._23, _m._33,
      _m._14, _m._24, _m._34
    );
  }

  void print() const noexcept {
    printf("| %.2f %.2f %.2f %.2f |\n", _m._11, _m._12, _m._13, _m._14);
    printf("| %.2f %.2f %.2f %.2f |\n", _m._21, _m._22, _m._23, _m._24);
    printf("| %.2f %.2f %.2f %.2f |\n", _m._31, _m._32, _m._33, _m._34);
  }

  const char* to_string() const noexcept {
    static char buffer[160];
    std::snprintf(buffer, sizeof(buffer),
                  "| %.2f %.2f %.2f %.2f |\n| %.2f %.2f %.2f %.2f |\n| %.2f %.2f %.2f %.2f |",
                  _m._11, _m._12, _m._13, _m._14, _m._21, _m._22, _m._23, _m._24, _m._31, _m._32, _m._33, _m._34);
    return buffer;
  }

#if (__cplusplus >= 202002L)
  constexpr bool operator==(const matrix3x4& other) const noexcept = default;
  constexpr auto operator<=>(const matrix3x4& other) const noexcept = default;
#else
  constexpr bool operator==(const matrix3x4& other) const noexcept {
    return _m._11 == other._m._11 && _m._12 == other._m._12 && _m._13 == other._m._13 && _m._14 == other._m._14 &&
    _m._21 == other._m._21 && _m._22 == other._m._22 && _m._23 == other._m._23 && _m._24 == other._m._24 &&
    _m._31 == other._m._31 && _m._32 == other._m._32 && _m._33 == other._m._33 && _m._34 == other._m._34;
  }
#endif
};

} // namespace cgmath

