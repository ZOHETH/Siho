#include <iostream>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/pbrmaterial.h>

int main()
{
    // ����һ��Importer����
    Assimp::Importer importer;

    // ����gltfģ���ļ�
    const aiScene* scene = importer.ReadFile("C:\\3D Models\\lamp.gltf", aiProcess_Triangulate | aiProcess_FlipUVs);

    // ����Ƿ���سɹ�
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cout << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
        return -1;
    }

    // ���������е����в���
    for (unsigned int i = 0; i < scene->mNumMaterials; i++)
    {
        // ��ȡ��i������
        aiMaterial* material = scene->mMaterials[i];

        // ��ӡ���ʵ�����
        aiString name;
        material->Get(AI_MATKEY_NAME, name);
        std::cout << "Material " << i << ": " << name.C_Str() << std::endl;

        // ��ӡ���ʵĻ�����ɫ
        aiColor4D baseColor;
        material->Get(AI_MATKEY_BASE_COLOR, baseColor);
        std::cout << "Base color: (" << baseColor.r << ", " << baseColor.g << ", " << baseColor.b << ", " << baseColor.a << ")" << std::endl;

        // ��ӡ���ʵĽ�����
        float metallic;
        material->Get(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLIC_FACTOR, metallic);
        std::cout << "Metallic: " << metallic << std::endl;

        // ��ӡ���ʵĴֲڶ�
        float roughness;
        material->Get(AI_MATKEY_ROUGHNESS_FACTOR, roughness);
        std::cout << "Roughness: " << roughness << std::endl;

        // ��ӡ���ʵĻ�����ɫ����
        aiString baseColorTexture;
        material->GetTexture(AI_MATKEY_BASE_COLOR_TEXTURE, &baseColorTexture);
        std::cout << "Base color texture: " << baseColorTexture.C_Str() << std::endl;

        // ��ӡ���ʵĽ����Ⱥʹֲڶ�����
        aiString metallicRoughnessTexture;
        material->GetTexture(AI_MATKEY_GLTF_PBRMETALLICROUGHNESS_METALLICROUGHNESS_TEXTURE, &metallicRoughnessTexture);
        std::cout << "Metallic roughness texture: " << metallicRoughnessTexture.C_Str() << std::endl;

        // ��ӡ���ʵķ�������
        aiString normalTexture;
        material->GetTexture(aiTextureType_NORMALS, 0, &normalTexture);
        std::cout << "Normal texture: " << normalTexture.C_Str() << std::endl;

        // ��ӡ���ʵ��ڵ�����
        aiString occlusionTexture;
        material->GetTexture(aiTextureType_AMBIENT_OCCLUSION, 0, &occlusionTexture);
        std::cout << "Occlusion texture: " << occlusionTexture.C_Str() << std::endl;

        // ��ӡ���ʵ��Է�������
        aiString emissiveTexture;
        material->GetTexture(aiTextureType_EMISSIVE, 0, &emissiveTexture);
        std::cout << "Emissive texture: " << emissiveTexture.C_Str() << std::endl;

        // ��ӡ���ʵ�͸����
        float opacity;
        material->Get(AI_MATKEY_OPACITY, opacity);
        std::cout << "Opacity: " << opacity << std::endl;

        // ��ӡ���ʵ�������
        float ior;
        material->Get(AI_MATKEY_REFRACTI, ior);
        std::cout << "Index of refraction: " << ior << std::endl;

        // ��ӡ���ʵ�˫����
        int twoSided;
        material->Get(AI_MATKEY_TWOSIDED, twoSided);
        std::cout << "Two sided: " << (twoSided ? "true" : "false") << std::endl;

        // ��ӡ���ʵĻ��ģʽ
        aiBlendMode blendMode;
        material->Get(AI_MATKEY_BLEND_FUNC, blendMode);
        std::cout << "Blend mode: " << blendMode << std::endl;

        // ��ӡһ������
        std::cout << std::endl;
    }

    return 0;
}
