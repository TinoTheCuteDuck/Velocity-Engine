#include <utility>

#include "rendering/meshInstance.hpp"

#include "core/engine.hpp"
#include "math/vector/vector4.hpp"
#include "rendering/renderingTypes.hpp"

MeshInstance::MeshInstance(std::string  filePath, const unsigned int componentID) : componentID(componentID), filePath(std::move(filePath)) {
    generateMeshInstanceData();
    color.onChanged = [this]([[maybe_unused]] const Vector3& newColor) {
        this->generateMeshInstanceData();
    };
    opacity.onChanged = [this]([[maybe_unused]] const float newOpacity) {
        this->generateMeshInstanceData();
    };
}

MeshInstance::MeshInstance(MeshInstance&& other) noexcept {
    componentID = other.componentID;
    filePath = std::move(other.filePath);
    color = std::move(other.color);
    opacity = std::move(other.opacity);

    generateMeshInstanceData();
    color.onChanged = [this]([[maybe_unused]] const Vector3& newColor) {
        this->generateMeshInstanceData();
    };
    opacity.onChanged = [this]([[maybe_unused]] const float newOpacity) {
        this->generateMeshInstanceData();
    };
}

void MeshInstance::generateMeshInstanceData() const {
    const MeshInstanceData data{Vector4(color.get(), opacity.get())};
    Engine::get().renderer.changeMeshUBO(componentID, data);
}