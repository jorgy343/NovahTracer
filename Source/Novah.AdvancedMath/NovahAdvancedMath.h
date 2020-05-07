#pragma once

// Standard includes that are needed here and there.
#include <vector>
#include <unordered_map>

// Compile time options.
#define InstructionSetsFma3

// Constants.
const float Epsilon = 0.001f;

// Create the striped down class definitions.
template <typename T>
class Color3T;

template <typename T>
class Color4T;

template <typename T>
class Vector2T;

template <typename T>
class Vector3T;

template <typename T>
class Vector4T;

template <typename T>
class MatrixT;

template <typename T>
class QuaternionT;

// Include all header files.
#include "Color3T.h"
#include "Color4T.h"

#include "Vector2T.h"
#include "Vector3T.h"
#include "Vector4T.h"

#include "MatrixT.h"

#include "Color3.h"
#include "Color4.h"

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

#include "Matrix.h"
#include "QuaternionT.h"

#include "IntersectionData.h"

#include "CsgOperation.h"
#include "Surface.h"
#include "Ray.h"
#include "Plane.h"
#include "RectangularFrustum.h"
#include "Cylinder.h"
#include "Parallelogram.h"
#include "Sphere.h"
#include "AxisAlignedRectangularBox.h"
#include "Quadric.h"
#include "CsgSurface.h"
#include "TransformedSurface.h"
#include "SurfaceGroup.h"
#include "BoundingSurface.h"

#include "BoundingVolume.h"
#include "BoundingSphere.h"