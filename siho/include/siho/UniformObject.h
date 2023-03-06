#pragma once
#include <string>
#include <unordered_map>
#include <variant>
#include <glm/glm.hpp>

using std::string;

namespace uniforms
{
	static const string kModel = "model";
	static const string kView = "view";
	static const string kProjection = "projection";

	static const string kBaseColorFactor = "material.baseColorFactor";
	static const string kSpecularColorFactor = "material.specularColorFactor";
	static const string kEmissiveFactor = "material.emissiveFactor";

	static const string kMetallicFactor = "material.metallicFactor";
	static const string kRoughnessFactor = "material.roughnessFactor";
	static const string kIor = "material.ior";

	static const string kBaseColorTexture = "material.baseColorTexture";
	static const string kMetallicRoughnessTexture = "material.metallicRoughnessTexture";
	static const string kNormalTexture = "material.normalTexture";
	static const string kEmissiveTexture = "material.emissiveTexture";

	static const string kPointLightPrefix = "point_lights";
	static const string kSpotLightPrefix = "spot_lights";
	static const string kPointLightsCount = "point_lights_count";
	static const string kSpotLightsCount = "spot_lights_count";

	enum class Light
	{
		POSITION,
		DIRECTION,
		COLOR,
		INTENSITY,
		CUTOFF,
		OUTER_CUTOFF
	};
	inline std::string PointLight(const int index, const Light uniform)
	{
		return kPointLightPrefix + "[" + std::to_string(index) + "]." + [&]
		{
			switch (uniform)
			{
			case Light::POSITION: return "position";
			case Light::COLOR: return "color";
			case Light::INTENSITY: return "intensity";
			default: return "";
			}
		}();
	}

	inline std::string SpotLight(const int index, const Light uniform)
	{
		return kSpotLightPrefix + "[" + std::to_string(index) + "]." + [&]
		{
			switch (uniform)
			{
			case Light::POSITION: return "position";
			case Light::DIRECTION: return "direction";
			case Light::COLOR: return "color";
			case Light::INTENSITY: return "intensity";
			case Light::CUTOFF: return "cutoff";
			case Light::OUTER_CUTOFF: return "outerCutoff";
			default: return "";
			}
		}();
	}
}

class Shader;

class UniformObject
{
public:
	using UniformData =
	std::variant<bool, float, int, unsigned int,
	             glm::vec2, glm::vec3, glm::vec4,
	             glm::mat2, glm::mat3, glm::mat4>;

	template <typename T>
	void set(const std::string& name, const T& value);

	void apply(const Shader& shader) const;

private:
	std::unordered_map<std::string, UniformData> uniform_data_{};
};