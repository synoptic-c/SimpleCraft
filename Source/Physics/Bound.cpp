#include"Bound.hpp"
void SimpleCraft::from_json(const nlohmann::json& json, SimpleCraft::Bound& bound)
{
	json["left"].get_to<float>(bound.left);
	json["right"].get_to<float>(bound.right);
	json["bottom"].get_to<float>(bound.bottom);
	json["top"].get_to<float>(bound.top);
}