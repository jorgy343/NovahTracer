#include "NovahTracerEngine.h"

ParallelogramLight::ParallelogramLight(const Color3& color, const Vector3& corner, const Vector3& edge1, const Vector3& edge2, int sampleLevel, ParallelogramLightSampleMode parallelogramLightSampleMode)
    : Light(color), _corner(corner), _edge1(edge1), _edge2(edge2),
    _sampleLevel(sampleLevel), _parallelogramLightSampleMode(parallelogramLightSampleMode)
{

}

float ParallelogramLight::GetShadowPowerRandom(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    float power = (float)_sampleLevel;
    for (int i = 0; i < _sampleLevel; ++i)
    {
        Vector3 pointOnLight = _corner + _random.GetNormalizedFloat() * _edge1 + _random.GetNormalizedFloat() * _edge2;

        Vector3 directionToLight = (pointOnLight - point).Normalize();
        Ray ray(point + Epsilon * directionToLight, directionToLight);
        float distanceToLight = (pointOnLight - point).GetLength();

        IntersectionData intersectionData;
        for (int i = 0; i < surfaceCount; ++i)
        {
            if (surfaces[i]->IntersectRay(ray, &intersectionData) && intersectionData.GetDistance() <= distanceToLight)
            {
                power -= 1.0f;
                continue;
            }
        }
    }

    return power / (float)_sampleLevel;
}

float ParallelogramLight::GetShadowPowerRegular(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const* surfaces, int surfaceCount) const
{
    float totalSamples = _sampleLevel * _sampleLevel;

    float power = totalSamples;
    float segmentSize = 1.0f / (float)_sampleLevel;

    for (int edge2Index = 0; edge2Index < _sampleLevel; ++edge2Index)
    {
        for (int edge1Index = 0; edge1Index < _sampleLevel; ++edge1Index)
        {
            float edge1Offset = segmentSize * edge1Index + 0.5f * segmentSize;
            float edge2Offset = segmentSize * edge2Index + 0.5f * segmentSize;

            Vector3 pointOnLight = _corner + edge1Offset * _edge1 + edge2Offset * _edge2;

            Vector3 directionToLight = (pointOnLight - point).Normalize();
            Ray ray(point + Epsilon * directionToLight, directionToLight);
            float distanceToLight = (pointOnLight - point).GetLength();

            IntersectionData intersectionData;
            for (int i = 0; i < surfaceCount; ++i)
            {
                if (surfaces[i]->IntersectRay(ray, &intersectionData) && intersectionData.GetDistance() <= distanceToLight)
                {
                    power -= 1.0f;
                    continue;
                }
            }
        }
    }

    return power / totalSamples;
}

float ParallelogramLight::GetShadowPowerRegularRandom(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    float totalSamples = _sampleLevel * _sampleLevel;

    float power = totalSamples;
    float segmentSize = 1.0f / (float)_sampleLevel;

    for (int edge2Index = 0; edge2Index < _sampleLevel; ++edge2Index)
    {
        float edge2Offset = segmentSize * edge2Index + _random.GetNormalizedFloat() * segmentSize;
        Vector3 edge2Constent = edge2Offset * _edge2;

        for (int edge1Index = 0; edge1Index < _sampleLevel; ++edge1Index)
        {
            float edge1Offset = segmentSize * edge1Index + _random.GetNormalizedFloat() * segmentSize;
            Vector3 pointOnLight = _corner + edge1Offset * _edge1 + edge2Constent;

            Vector3 directionToLight = (pointOnLight - point).Normalize();
            Ray ray(point + Epsilon * directionToLight, directionToLight);
            float distanceToLight = (pointOnLight - point).GetLength();

            IntersectionData intersectionData;
            for (int i = 0; i < surfaceCount; ++i)
            {
                if (surfaces[i]->IntersectRay(ray, &intersectionData) && intersectionData.GetDistance() <= distanceToLight)
                {
                    power -= 1.0f;
                    continue;
                }
            }
        }
    }

    return power / totalSamples;
}

float ParallelogramLight::GetShadowPower(const Ray& viewRay, const Vector3& point, const Vector3& normal, const Surface* const * surfaces, int surfaceCount) const
{
    switch (_parallelogramLightSampleMode)
    {
    case ParallelogramLightSampleMode::Random:
        return GetShadowPowerRandom(viewRay, point, normal, surfaces, surfaceCount);

    case ParallelogramLightSampleMode::Regular:
        return GetShadowPowerRegular(viewRay, point, normal, surfaces, surfaceCount);

    case ParallelogramLightSampleMode::RegularRandom:
        return GetShadowPowerRegularRandom(viewRay, point, normal, surfaces, surfaceCount);
    }

    return 0.0f;
}

void ParallelogramLight::GetLightPowers(const Ray& viewRay, const Vector3& point, const Vector3& normal, float* diffusePower, float* specularPower) const
{
    *diffusePower = 0.0f;
    *specularPower = 0.0f;

    float segmentSize = 1.0f / (float)_sampleLevel;
    for (int edge2Index = 0; edge2Index < _sampleLevel; ++edge2Index)
    {
        for (int edge1Index = 0; edge1Index < _sampleLevel; ++edge1Index)
        {
            float random1 = (float)(rand() % RAND_MAX) / (float)RAND_MAX;
            float random2 = (float)(rand() % RAND_MAX) / (float)RAND_MAX;

            float edge1Offset = segmentSize * edge1Index + random1 * segmentSize;
            float edge2Offset = segmentSize * edge2Index + random2 * segmentSize;

            Vector3 pointOnLight = _corner + edge1Offset * _edge1 + edge2Offset * _edge2;

            Vector3 directionToLight = (pointOnLight - point).Normalize();
            Vector3 lightReflectionOffNormal = Vector3::Reflect(directionToLight, normal).Normalize();

            *diffusePower += std::max(0.0f, Vector3::Dot(normal, directionToLight));
            *specularPower += Vector3::Dot(lightReflectionOffNormal, Vector3::Negate(viewRay.Direction));
        }
    }

    *diffusePower = *diffusePower / (float)(_sampleLevel * _sampleLevel);
    *specularPower = *specularPower / (float)(_sampleLevel * _sampleLevel);
}

Vector3 ParallelogramLight::GetCorner() const
{
    return _corner;
}

void ParallelogramLight::SetCorner(const Vector3& corner)
{
    _corner = corner;
}

Vector3 ParallelogramLight::GetEdge1() const
{
    return _edge1;
}

void ParallelogramLight::SetEdge1(const Vector3& edge1)
{
    _edge1 = edge1;
}

Vector3 ParallelogramLight::GetEdge2() const
{
    return _edge2;
}

void ParallelogramLight::SetEdge2(const Vector3& edge2)
{
    _edge2 = edge2;
}