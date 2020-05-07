#include "NovahTracerEngine.h"

Scene::Scene(
    const Color3& backgroundColor,
    float defaultRefractionIndex,
    int antiAliasingLevel,
    const Surface* rootSurface,
    const std::unordered_map<const Surface*, const MaterialBase*>* surfaceMaterialMap,
    const std::vector<const Light*>* lights)
    : _backgroundColor(backgroundColor),
        _defaultRefractionIndex(defaultRefractionIndex),
        _antiAliasingLevel(antiAliasingLevel),
        _rootSurface(rootSurface),
        _surfaceMaterialMap(surfaceMaterialMap),
        _lights(lights)
{
    for (const auto& surfaceMaterial : *surfaceMaterialMap)
    {
        if (surfaceMaterial.second->GetLightOccluder())
            _lightOccluders.push_back(surfaceMaterial.first);
    }
}

Color3 Scene::CastRay(const Ray& ray) const
{
    return CastRay(ray, 0);
}

Color3 Scene::CastRay(const Ray& ray, int depth) const
{
    IntersectionData foundIntersectionData;
    const Surface* foundSurface = _rootSurface->IntersectRay(ray, &foundIntersectionData);

    if (foundSurface != nullptr)
    {
        if (_surfaceMaterialMap->count(foundIntersectionData.GetDetailedSurface()) == 1)
        {
            MaterialBase* material = const_cast<MaterialBase*>(_surfaceMaterialMap->at(foundIntersectionData.GetDetailedSurface())); // TODO: const hack

            Color3 summedDiffuseLight(0.0f);
            Color3 summedSpecularLight(0.0f);

            for (const auto& light : *_lights)
            {
                float shadowPower = 1.0f;
                if (material->GetShadowReceiver())
                {
                    shadowPower = light->GetShadowPower(ray, foundIntersectionData.GetPoint(), foundIntersectionData.GetNormal(), _lightOccluders.data(), _lightOccluders.size());
                    if (shadowPower == 0.0f)
                        continue;
                }

                float diffusePower;
                float specularPower;

                light->GetLightPowers(ray, foundIntersectionData.GetPoint(), foundIntersectionData.GetNormal(), &diffusePower, &specularPower);
            
                summedDiffuseLight += shadowPower * diffusePower * light->GetColor();
                summedSpecularLight += shadowPower * pow(specularPower, material->GetSpecularPower()) * light->GetColor();
            }

            Color3 reflectionRayColor(0.0f);
            Color3 refractionRayColor(0.0f);

            float reflectionCoefficient = 1.0f;
            float refractionCoefficient = 1.0f;

            if (material->GetReflectionCoefficient() > 0.0f && material->GetRefractionCoefficient() > 0.0f)
            {
                reflectionCoefficient = Vector3::SchlickApproximation(ray.Direction, foundIntersectionData.GetNormal(), 1.0f, material->GetRefractionIndex());
                refractionCoefficient = 1.0f - reflectionCoefficient;
            }

            if (depth < 8 && material->GetReflectionCoefficient() > 0.0f)
            {
                Vector3 reflectionDirection = Vector3::Reflect(ray.Direction, foundIntersectionData.GetNormal()).Normalize();
                Ray reflectionRay(foundIntersectionData.GetPoint() + Epsilon * reflectionDirection, reflectionDirection);

                reflectionRayColor = CastRay(reflectionRay, depth + 1);
            }

            if (depth < 8 && material->GetRefractionCoefficient() > 0.0f)
            {
                Vector3 refractionDirection = Vector3::Refract(ray.Direction, foundIntersectionData.GetNormal(), 1.0f, material->GetRefractionIndex());
                if (!refractionDirection.IsZeroVector())
                {
                    refractionDirection.Normalize();
                    Ray refractionRay(foundIntersectionData.GetPoint(), refractionDirection);

                    std::vector<IntersectionData> refractionIntersectionData;
                    foundSurface->IntersectRay(refractionRay, &refractionIntersectionData);

                    if (refractionIntersectionData.size() > 1)
                    {
                        Vector3 newDirection = Vector3::Refract(refractionRay.Direction, -refractionIntersectionData[1].GetNormal(), material->GetRefractionIndex(), 1.0f);
                        if (!newDirection.IsZeroVector())
                        {
                            newDirection.Normalize();

                            Ray newRay(refractionIntersectionData[1].GetPoint() + newDirection * Epsilon, newDirection);
                            refractionRayColor = CastRay(newRay, depth + 1);
                        }
                    }
                }
            }

            Vector3 point = foundIntersectionData.GetPoint();
            Vector3 normal = foundIntersectionData.GetNormal();

            Color3 color = material->CalculateColor(&point, &normal);
            Color3 specularColor = material->CalculateSpecularColor(&foundIntersectionData.GetPoint(), &foundIntersectionData.GetNormal());

            Color3 ambientColor = material->GetAmbientCoefficient() * color;
            Color3 diffuseColor = material->GetDiffuseCoefficient() * color * summedDiffuseLight;
            specularColor = specularColor * material->GetSpecularCoefficient() * summedSpecularLight;
            Color3 reflectionColor = material->GetReflectionCoefficient() * reflectionRayColor * reflectionCoefficient;
            Color3 refractionColor = material->GetRefractionCoefficient() * refractionRayColor * refractionCoefficient;
            
            //return Color3((foundIntersectionData.GetNormal().X + 1.0f) / 2.0f, (foundIntersectionData.GetNormal().Y + 1.0f) / 2.0f, (foundIntersectionData.GetNormal().Z + 1.0f) / 2.0f);
            return (ambientColor + diffuseColor + specularColor + reflectionColor + refractionColor).Clamp(Color3(0.0f), Color3(1.0f));
        }
    }

    return _backgroundColor;
}

void Scene::SetRootSurface(const Surface* rootSurface)
{
    _rootSurface = rootSurface;
}

PropertyGetSetImplementation(int, Scene, antiAliasingLevel, AntiAliasingLevel)