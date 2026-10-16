// Compatibility shim for Geometry Dash 2.2074 on Windows.
//
// Geode 4.6.3's generated bindings for
// SpriteAnimationManager::offsetCurrentAnimation call
// CCActionInterval::getM_bFirstTick(). The SDK's Cocos header declares
// this accessor, but the supplied Windows Cocos import library does not
// provide it, producing an unresolved external at link time.
//
// The backing bool is a public member of CCActionInterval; implement
// the accessor directly instead of relying on an unavailable export.
#include <Geode/Geode.hpp>
#include <Geode/cocos/actions/CCActionInterval.h>

#ifdef GEODE_IS_WINDOWS
namespace cocos2d {
    bool CCActionInterval::getM_bFirstTick() {
        return m_bFirstTick;
    }
}
#endif
