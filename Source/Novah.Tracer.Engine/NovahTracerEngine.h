#pragma once

#define _USE_MATH_DEFINES

#define PropertyGetSetDeclaration(type, nameLower, nameUpper) \
    type Get ## nameUpper() const; \
    void Set ## nameUpper(type nameLower);

#define PropertyGetSetImplementation(type, class, nameLower, nameUpper) \
    type class::Get ## nameUpper() const { return _ ## nameLower; } \
    void class::Set ## nameUpper(type nameLower) { _ ## nameLower = nameLower; }

#include "PerlinNoise.h"

#include "NovahAdvancedMath.h"
#include "Random.h"

#include "MaterialBase.h"
#include "BasicMaterial.h"
#include "FunctionMaterial.h"
#include "LuaMaterial.h"
#include "MaterialSurface.h"

#include "Camera.h"
#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

#include "ParallelogramLightSampleMode.h"
#include "Light.h"
#include "AttenuatedLight.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "SphericalLight.h"
#include "ParallelogramLight.h"
#include "AttenuatedPointLight.h"

#include "Scene.h"

#include "XmlSceneLoader.h"