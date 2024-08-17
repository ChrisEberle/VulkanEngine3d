﻿// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>

#include "vk_descriptors.h"
#include <unordered_map>
#include <filesystem>

class VulkanEngine;

struct Bounds {
    glm::vec3 origin;
    float sphereRadius;
    glm::vec3 extents;
};

struct GLTFMaterial {
    MaterialInstance data;
};

struct GeoSurface {
    uint32_t startIndex;
    uint32_t count;
    Bounds bounds;
	std::shared_ptr<GLTFMaterial> material;
};

struct MeshAsset {
    std::string name;
    std::vector<GeoSurface> surfaces;
    GPUMeshBuffers meshBuffers;
};

struct LoadedGLTF : public IRenderable {

    // storage for all the data on a given gltf file
    std::unordered_map<std::string, std::shared_ptr<MeshAsset>> meshes;
    std::unordered_map<std::string, std::shared_ptr<Node>> nodes;
    std::unordered_map<std::string, AllocatedImage> images;
    std::unordered_map<std::string, std::shared_ptr<GLTFMaterial>> materials;

    // nodes that dont have a parent, for iterating through the file in tree order
    std::vector<std::shared_ptr<Node>> topNodes;

    std::vector<VkSampler> samplers;

    DescriptorAllocatorGrowable descriptorPool;

    AllocatedBuffer materialDataBuffer;

    VulkanEngine* creator;

    ~LoadedGLTF() { clearAll(); };

    virtual void Draw(const glm::mat4& topMatrix, DrawContext& ctx);

void print_meshes()
{
    // Print all meshes
    fmt::print("Meshes:\n");
    for (const auto& [name, meshPtr] : meshes) {
        if (meshPtr) {
            fmt::print("  Mesh Name: {}\n", meshPtr->name);  // Access and print the name of the MeshAsset
        } else {
            fmt::print("  Mesh Name: {} -> (null)\n", name);  // Handle null pointer case
        }
    }

    // Other printing code for nodes, images, materials, etc. can go here, using fmt::print
}
void print_nodes()
{
    // Print all nodes
    fmt::print("Nodes:\n");
    for (const auto& [name, nodePtr] : nodes) {
            fmt::print("  Node Name: {}\n", name);  // Print the name of the Node
    }
    // Additional printing code for meshes, images, materials, etc., can be added here
}
private:

    void clearAll();
};

std::optional<std::shared_ptr<LoadedGLTF>> loadGltf(VulkanEngine* engine, std::string_view filePath);