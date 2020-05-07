#pragma once

#include "NovahTracerEngine.h"
#include "PugiConfig.h"
#include "pugi.h"

using namespace Novah::AdvancedMath;

class MaterialContainer
{
public:
    std::unordered_map<std::string, MaterialBase*>* MaterialMap;
    std::unordered_map<const Surface*, const MaterialBase*>* SurfaceMaterialMap;
};

class XmlSceneLoader
{
private:
    pugi::xml_document _document;

    void ConsumeWhitespace(std::stringstream& stream) const;

    Color3 ParseColor3(const char* string) const;
    Color4 ParseColor4(const char* string) const;

    Vector2 ParseVector2(const char* string) const;
    Vector3 ParseVector3(const char* string) const;
    Vector4 ParseVector4(const char* string) const;

    Matrix ParseMatrix(const pugi::xml_node element) const;
    Matrix ParseMatrixStack(const pugi::xml_node element) const;

    PerspectiveCamera* ParsePerspectiveCamera(const pugi::xml_node element) const;

    Surface* ParseRootSurface(MaterialContainer* materialContainer) const;
    Surface* ParseSurface(const pugi::xml_node element, MaterialContainer* materialContainer) const;
    Surface* ParseSurfaceGroup(const pugi::xml_node element, MaterialContainer* materialContainer) const;
    Surface* ParseTransformedSurface(const pugi::xml_node element, MaterialContainer* materialContainer) const;
    Surface* ParseCsg(const pugi::xml_node element, MaterialContainer* materialContainer) const;
    Surface* ParsePlane(const pugi::xml_node element) const;
    Surface* ParseSphere(const pugi::xml_node element) const;
    Surface* ParseAxisAlignedRectangularBox(const pugi::xml_node element) const;

    std::vector<const Light*>* ParseLights() const;

public:
    XmlSceneLoader(const char* xmlContent);

    std::unordered_map<std::string, MaterialBase*>* ParseMaterialMap() const;

    Scene* CreateScene(MaterialContainer* materialContainer) const;
    Camera* CreateCamera() const;
};