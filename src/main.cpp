#include <Geode/Geode.hpp>

using namespace geode::prelude;

// Phase 0 smoke test: prove the mod loads and hooks fire.
#include <Geode/modify/MenuLayer.hpp>
class $modify(GDSolverMenuLayer, MenuLayer) {
	bool init() {
		if (!MenuLayer::init()) {
			return false;
		}
		log::info("gdsolver loaded: MenuLayer::init hook fired");
		return true;
	}
};

$execute {
	log::info("gdsolver: $execute ran (mod binary loaded)");
	log::warn("GD 2.2074 port: upstream 2.2081 raw memory layouts remain unverified; RNG modification disabled");
}
