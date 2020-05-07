#include "XmlSceneLoader.h"

#include <sstream>
#include <string>

XmlSceneLoader::XmlSceneLoader(const char* xmlContent)
{
    _document.load(xmlContent);
}

void XmlSceneLoader::ConsumeWhitespace(std::stringstream& stream) const
{
    char dummy;
    while (!stream.eof())
    {
        char character = stream.peek();
        switch (stream.peek())
        {
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            stream.read(&dummy, 1);
            continue;
        }

        break;
    }
}

Color3 XmlSceneLoader::ParseColor3(const char* string) const
{
    std::stringstream stream(string);

    Color3 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.Red;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Green;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Blue;

    return result;
}

Color4 XmlSceneLoader::ParseColor4(const char * string) const
{
    std::stringstream stream(string);

    Color4 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.Red;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Green;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Blue;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Alpha;

    return result;
}

Vector2 XmlSceneLoader::ParseVector2(const char * string) const
{
    std::stringstream stream(string);

    Vector2 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.X;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Y;

    return result;
}

Vector3 XmlSceneLoader::ParseVector3(const char* string) const
{
    std::stringstream stream(string);

    Vector3 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.X;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Y;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Z;

    return result;
}

Vector4 XmlSceneLoader::ParseVector4(const char* string) const
{
    std::stringstream stream(string);

    Vector4 result;
    char dummy;

    ConsumeWhitespace(stream);
    stream >> result.X;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Y;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.Z;

    ConsumeWhitespace(stream);
    stream.read(&dummy, 1); // Read the comma.

    ConsumeWhitespace(stream);
    stream >> result.W;

    return result;
}

Matrix XmlSceneLoader::ParseMatrix(const pugi::xml_node element) const
{
    std::string elementName = element.name();
    if (elementName == "ScaleMatrix")
    {
        auto scale = ParseVector3(element.attribute("Scale").value());
        return Matrix::CreateScale(scale);
    }

    // Assume TranslateMatrix
    auto translation = ParseVector3(element.attribute("Translation").value());
    return Matrix::CreateTranslation(translation);
}

Matrix XmlSceneLoader::ParseMatrixStack(const pugi::xml_node element) const
{
    Matrix matrix = Matrix::CreateIdentity();
    for (auto& child : element.children())
        matrix = matrix * ParseMatrix(child);

    return matrix;
}

PerspectiveCamera* XmlSceneLoader::ParsePerspectiveCamera(const pugi::xml_node element) const
{
    auto position = ParseVector3(element.attribute("Position").value());
    auto lookAt = ParseVector3(element.attribute("LookAt").value());
    auto up = ParseVector3(element.attribute("Up").value());

    auto windowWidth = element.attribute("ScreenWidth").as_int();
    auto windowHeight = element.attribute("ScreenHeight").as_int();

    auto fieldOfView = element.attribute("FieldOfView").as_float();

    return new PerspectiveCamera(position, lookAt, up, windowWidth, windowHeight, fieldOfView);
}

Surface* XmlSceneLoader::ParseRootSurface(MaterialContainer* materialContainer) const
{
    auto rootSurfaceElement = _document.select_single_node("//RootSurface/*").node();
    return ParseSurface(rootSurfaceElement, materialContainer);
}

Surface* XmlSceneLoader::ParseSurface(const pugi::xml_node element, MaterialContainer* materialContainer) const
{
    std::string elementName = element.name();
    Surface* surface = nullptr;

    if (elementName == "SurfaceGroup")
        surface = ParseSurfaceGroup(element, materialContainer);
    else if (elementName == "TransformedSurface")
        surface = ParseTransformedSurface(element, materialContainer);
    else if (elementName == "Csg")
        surface = ParseCsg(element, materialContainer);
    else if (elementName == "Plane")
        surface = ParsePlane(element);
    else if (elementName == "Sphere")
        surface = ParseSphere(element);
    else if (elementName == "AxisAlignedRectangularBox")
        surface = ParseAxisAlignedRectangularBox(element);

    if (surface != nullptr)
    {
        std::string materialName = element.attribute("Material").as_string();
        if (materialContainer->MaterialMap->count(materialName) == 1)
        {
            MaterialBase* material = materialContainer->MaterialMap->at(materialName);
            materialContainer->SurfaceMaterialMap->insert(std::make_pair(surface, material));
        }
    }

    return surface;
}

Surface* XmlSceneLoader::ParseSurfaceGroup(const pugi::xml_node element, MaterialContainer* materialContainer) const
{
    auto surfaces = new std::vector<const Surface*>();
    for (auto& child : element.select_single_node("./Surfaces").node().children())
    {
        auto surface = ParseSurface(child, materialContainer);
        if (surface != nullptr)
            surfaces->push_back(surface);
    }

    return new SurfaceGroup(surfaces);
}

Surface* XmlSceneLoader::ParseTransformedSurface(const pugi::xml_node element, MaterialContainer* materialContainer) const
{
    auto matrixStackElement = element.select_single_node("./MatrixStack").node();
    auto surfaceElement = element.select_single_node("./Surface/*").node();

    Matrix matrix = ParseMatrixStack(matrixStackElement);
    Surface* surface = ParseSurface(surfaceElement, materialContainer);

    return new TransformedSurface(surface, matrix);
}

Surface* XmlSceneLoader::ParseCsg(const pugi::xml_node element, MaterialContainer* materialContainer) const
{
    auto leftSurfaceElement = element.select_single_node("./LeftSurface/*").node();
    auto rightSurfaceElement = element.select_single_node("./RightSurface/*").node();

    auto leftSurface = ParseSurface(leftSurfaceElement, materialContainer);
    auto rightSurface = ParseSurface(rightSurfaceElement, materialContainer);

    std::string operationString = element.attribute("Operation").value();
    CsgOperation operation = CsgOperation::Union; // Assume union by default.

    if (operationString == "Intersection")
        operation = CsgOperation::Intersection;
    else if (operationString == "Difference")
        operation = CsgOperation::Difference;

    return new CsgSurface(leftSurface, rightSurface, operation);
}

Surface* XmlSceneLoader::ParsePlane(const pugi::xml_node element) const
{
    auto normal = ParseVector3(element.attribute("Normal").value());
    auto point = ParseVector3(element.attribute("Point").value());

    return new Plane(normal, point);
}

Surface* XmlSceneLoader::ParseSphere(const pugi::xml_node element) const
{
    auto center = ParseVector3(element.attribute("Center").value());
    auto radius = element.attribute("Radius").as_float();

    return new Sphere(center, radius);
}

Surface* XmlSceneLoader::ParseAxisAlignedRectangularBox(const pugi::xml_node element) const
{
    auto minimum = ParseVector3(element.attribute("Minimum").value());
    auto maximum = ParseVector3(element.attribute("Maximum").value());

    return new AxisAlignedRectangularBox(minimum, maximum);
}

std::vector<const Light*>* XmlSceneLoader::ParseLights() const
{
    std::vector<const Light*>* lights = new std::vector<const Light*>();
    for (auto node : _document.select_nodes("//Lights/*"))
    {
        std::string elementName = node.node().name();
        if (elementName == "PointLight")
        {
            auto color = ParseColor3(node.node().attribute("Color").value());
            auto position = ParseVector3(node.node().attribute("Position").value());

            lights->push_back(new PointLight(color, position));
        }
        else if (elementName == "SphericalLight")
        {
            auto color = ParseColor3(node.node().attribute("Color").value());
            auto position = ParseVector3(node.node().attribute("Position").value());
            auto radius = node.node().attribute("Radius").as_float();

            lights->push_back(new SphericalLight(color, position, radius));
        }
        else if (elementName == "ParallelogramLight")
        {
            auto color = ParseColor3(node.node().attribute("Color").value());
            auto corner = ParseVector3(node.node().attribute("Corner").value());
            auto edge1 = ParseVector3(node.node().attribute("Edge1").value());
            auto edge2 = ParseVector3(node.node().attribute("Edge2").value());
            auto sampleLevel = node.node().attribute("SampleLevel").as_int();
            auto sampleMode = node.node().attribute("SampleMode").as_int();

            lights->push_back(new ParallelogramLight(color, corner, edge1, edge2, sampleLevel, (ParallelogramLightSampleMode)sampleMode));
        }
    }

    return lights;
}

std::unordered_map<std::string, MaterialBase*>* XmlSceneLoader::ParseMaterialMap() const
{
    std::unordered_map<std::string, MaterialBase*>* materialMap = new std::unordered_map<std::string, MaterialBase*>();
    for (auto node : _document.select_nodes("//Materials/*"))
    {
        std::string elementName = node.node().name();
        std::string name = node.node().attribute("Name").as_string();

        auto ambientCoefficient = node.node().attribute("AmbientCoefficient").as_float();
        auto diffuseCoefficient = node.node().attribute("DiffuseCoefficient").as_float();
        auto specularCoefficient = node.node().attribute("SpecularCoefficient").as_float();

        auto reflectionCoefficient = node.node().attribute("ReflectionCoefficient").as_float();
        auto refractionCoefficient = node.node().attribute("RefractionCoefficient").as_float();

        auto specularPower = node.node().attribute("SpecularPower").as_float();
        auto refractionIndex = node.node().attribute("RefractionIndex").as_float();

        auto lightOccluder = node.node().attribute("LightOccluder").as_bool();
        auto shadowReceiver = node.node().attribute("ShadowReceiver").as_bool();

        if (elementName == "BasicMaterial")
        {
            auto color = ParseColor3(node.node().attribute("Color").value());
            auto specularColor = ParseColor3(node.node().attribute("SpecularColor").value());

            auto material = new BasicMaterial(color, specularColor, ambientCoefficient, diffuseCoefficient, specularCoefficient, reflectionCoefficient, refractionCoefficient, specularPower, refractionIndex, lightOccluder, shadowReceiver);
            materialMap->insert(std::make_pair(name, material));
        }
        else if (elementName == "LuaMaterial")
        {
            auto luaCode = node.node().select_single_node("./LuaCode").node().text().as_string();

            auto material = new LuaMaterial(luaCode, ambientCoefficient, diffuseCoefficient, specularCoefficient, reflectionCoefficient, refractionCoefficient, specularPower, refractionIndex, lightOccluder, shadowReceiver);
            materialMap->insert(std::make_pair(name, material));
        }
    }

    return materialMap;
}

Scene* XmlSceneLoader::CreateScene(MaterialContainer* materialContainer) const
{
    auto sceneElement = _document.select_single_node("Scene").node();
    auto backgroundColor = ParseColor3(sceneElement.attribute("BackgroundColor").as_string());
    auto defaultRefractionIndex = sceneElement.attribute("DefaultRefractionIndex").as_float();
    auto antiAliasingLevel = sceneElement.attribute("AntialiasingLevel").as_int();

    return new Scene(
        backgroundColor,
        defaultRefractionIndex,
        antiAliasingLevel,
        ParseRootSurface(materialContainer),
        materialContainer->SurfaceMaterialMap,
        ParseLights());
}

Camera* XmlSceneLoader::CreateCamera() const
{
    auto perspectiveCameraElement = _document.select_single_node("//Camera/PerspectiveCamera").node();
    if (perspectiveCameraElement != nullptr)
        return ParsePerspectiveCamera(perspectiveCameraElement);

    return nullptr;
}