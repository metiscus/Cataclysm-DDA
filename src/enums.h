#pragma once
#ifndef ENUMS_H
#define ENUMS_H

#include <climits>
#include <ostream>
#include <utility>

class JsonOut;
class JsonIn;

template<typename T>
constexpr inline int sgn( const T x )
{
    return x < 0 ? -1 : ( x > 0 ? 1 : 0 );
}

//Used for autopickup and safemode rules
enum rule_state : int {
    RULE_NONE,
    RULE_WHITELISTED,
    RULE_BLACKLISTED
};

enum visibility_type {
    VIS_HIDDEN,
    VIS_CLEAR,
    VIS_LIT,
    VIS_BOOMER,
    VIS_DARK,
    VIS_BOOMER_DARK
};

enum special_game_id : int {
    SGAME_NULL = 0,
    SGAME_TUTORIAL,
    SGAME_DEFENSE,
    NUM_SPECIAL_GAMES
};

enum art_effect_passive : int {
    AEP_NULL = 0,
    // Good
    AEP_STR_UP, // Strength + 4
    AEP_DEX_UP, // Dexterity + 4
    AEP_PER_UP, // Perception + 4
    AEP_INT_UP, // Intelligence + 4
    AEP_ALL_UP, // All stats + 2
    AEP_SPEED_UP, // +20 speed
    AEP_PBLUE, // Reduces radiation
    AEP_SNAKES, // Summons friendly snakes when you're hit
    AEP_INVISIBLE, // Makes you invisible
    AEP_CLAIRVOYANCE, // See through walls
    AEP_SUPER_CLAIRVOYANCE, // See through walls to a great distance
    AEP_STEALTH, // Your steps are quieted
    AEP_EXTINGUISH, // May extinguish nearby flames
    AEP_GLOW, // Four-tile light source
    AEP_PSYSHIELD, // Protection from stare attacks
    AEP_RESIST_ELECTRICITY, // Protection from electricity
    AEP_CARRY_MORE, // Increases carrying capacity by 200
    AEP_SAP_LIFE, // Killing non-zombie monsters may heal you
    AEP_FUN, // Slight passive morale
    // Splits good from bad
    AEP_SPLIT,
    // Bad
    AEP_HUNGER, // Increases hunger
    AEP_THIRST, // Increases thirst
    AEP_SMOKE, // Emits smoke occasionally
    AEP_EVIL, // Addiction to the power
    AEP_SCHIZO, // Mimicks schizophrenia
    AEP_RADIOACTIVE, // Increases your radiation
    AEP_MUTAGENIC, // Mutates you slowly
    AEP_ATTENTION, // Draws netherworld attention slowly
    AEP_STR_DOWN, // Strength - 3
    AEP_DEX_DOWN, // Dex - 3
    AEP_PER_DOWN, // Per - 3
    AEP_INT_DOWN, // Int - 3
    AEP_ALL_DOWN, // All stats - 2
    AEP_SPEED_DOWN, // -20 speed
    AEP_FORCE_TELEPORT, // Occasionally force a teleport
    AEP_MOVEMENT_NOISE, // Makes noise when you move
    AEP_BAD_WEATHER, // More likely to experience bad weather
    AEP_SICK, // Decreases health over time
    AEP_CLAIRVOYANCE_PLUS, // See through walls to a larger distance; not bad effect, placement to preserve old saves.

    NUM_AEPS
};

enum artifact_natural_property {
    ARTPROP_NULL,
    ARTPROP_WRIGGLING, //
    ARTPROP_GLOWING, //
    ARTPROP_HUMMING, //
    ARTPROP_MOVING, //
    ARTPROP_WHISPERING, //
    ARTPROP_BREATHING, //
    ARTPROP_DEAD, //
    ARTPROP_ITCHY, //
    ARTPROP_GLITTERING, //
    ARTPROP_ELECTRIC, //
    ARTPROP_SLIMY, //
    ARTPROP_ENGRAVED, //
    ARTPROP_CRACKLING, //
    ARTPROP_WARM, //
    ARTPROP_RATTLING, //
    ARTPROP_SCALED,
    ARTPROP_FRACTAL,
    ARTPROP_MAX
};

enum phase_id : int {
    PNULL, SOLID, LIQUID, GAS, PLASMA
};

// Return the class an in-world object uses to interact with the world.
//   ex; if ( player.grab_type == OBJECT_VEHICLE ) { ...
//   or; if ( baseactor_just_shot_at.object_type() == OBJECT_NPC ) { ...
enum object_type {
    OBJECT_NONE,      // Nothing, invalid.
    OBJECT_ITEM,      // item.h
    OBJECT_ACTOR,     // potential virtual base class, get_object_type() would return one of the types below
    OBJECT_PLAYER,  // player.h, npc.h
    OBJECT_NPC,   // nph.h
    OBJECT_MONSTER, // monster.h
    OBJECT_VEHICLE,   // vehicle.h
    OBJECT_TRAP,      // trap.h
    OBJECT_FIELD,     // field.h; field_entry
    OBJECT_TERRAIN,   // Not a real object
    OBJECT_FURNITURE, // Not a real object
    NUM_OBJECTS,
};

struct point {
    int x = 0;
    int y = 0;
    constexpr point() = default;
    constexpr point( int X, int Y ) : x( X ), y( Y ) {}

    constexpr point operator+( const point &rhs ) const {
        return point( x + rhs.x, y + rhs.y );
    }
    point &operator+=( const point &rhs ) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    constexpr point operator-( const point &rhs ) const {
        return point( x - rhs.x, y - rhs.y );
    }
    point &operator-=( const point &rhs ) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
};

void serialize( const point &p, JsonOut &jsout );
void deserialize( point &p, JsonIn &jsin );

// Make point hashable so it can be used as an unordered_set or unordered_map key,
// or a component of one.
namespace std
{
template <>
struct hash<point> {
    std::size_t operator()( const point &k ) const {
        constexpr uint64_t a = 2862933555777941757;
        size_t result = k.y;
        result *= a;
        result += k.x;
        return result;
    }
};
}

inline constexpr bool operator<( const point &a, const point &b )
{
    return a.x < b.x || ( a.x == b.x && a.y < b.y );
}
inline constexpr bool operator==( const point &a, const point &b )
{
    return a.x == b.x && a.y == b.y;
}
inline constexpr bool operator!=( const point &a, const point &b )
{
    return !( a == b );
}

struct tripoint {
    int x = 0;
    int y = 0;
    int z = 0;
    constexpr tripoint() = default;
    constexpr tripoint( int X, int Y, int Z ) : x( X ), y( Y ), z( Z ) {}
    explicit constexpr tripoint( const point &p, int Z ) : x( p.x ), y( p.y ), z( Z ) {}

    constexpr tripoint operator+( const tripoint &rhs ) const {
        return tripoint( x + rhs.x, y + rhs.y, z + rhs.z );
    }
    constexpr tripoint operator-( const tripoint &rhs ) const {
        return tripoint( x - rhs.x, y - rhs.y, z - rhs.z );
    }
    tripoint &operator+=( const tripoint &rhs ) {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }
    constexpr tripoint operator-() const {
        return tripoint( -x, -y, -z );
    }
    /*** some point operators and functions ***/
    constexpr tripoint operator+( const point &rhs ) const {
        return tripoint( x + rhs.x, y + rhs.y, z );
    }
    constexpr tripoint operator-( const point &rhs ) const {
        return tripoint( x - rhs.x, y - rhs.y, z );
    }
    tripoint &operator+=( const point &rhs ) {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
    tripoint &operator-=( const point &rhs ) {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }
    tripoint &operator-=( const tripoint &rhs ) {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    void serialize( JsonOut &jsout ) const;
    void deserialize( JsonIn &jsin );
};

inline std::ostream &operator<<( std::ostream &os, const tripoint &pos )
{
    return os << pos.x << "," << pos.y << "," << pos.z;
}

// Make tripoint hashable so it can be used as an unordered_set or unordered_map key,
// or a component of one.
namespace std
{
template <>
struct hash<tripoint> {
    std::size_t operator()( const tripoint &k ) const {
        constexpr uint64_t a = 2862933555777941757;
        size_t result = k.z;
        result *= a;
        result += k.y;
        result *= a;
        result += k.x;
        return result;
    }
};
}

inline constexpr bool operator==( const tripoint &a, const tripoint &b )
{
    return a.x == b.x && a.y == b.y && a.z == b.z;
}
inline constexpr bool operator!=( const tripoint &a, const tripoint &b )
{
    return !( a == b );
}
inline bool operator<( const tripoint &a, const tripoint &b )
{
    if( a.x != b.x ) {
        return a.x < b.x;
    }
    if( a.y != b.y ) {
        return a.y < b.y;
    }
    if( a.z != b.z ) {
        return a.z < b.z;
    }
    return false;
}

static constexpr tripoint tripoint_min { INT_MIN, INT_MIN, INT_MIN };
static constexpr tripoint tripoint_zero { 0, 0, 0 };

struct sphere {
    int radius = 0;
    tripoint center = tripoint( 0, 0, 0 );

    sphere() = default;
    explicit sphere( const tripoint &center ) : radius( 1 ), center( center ) {}
    explicit sphere( const tripoint &center, int radius ) : radius( radius ), center( center ) {}
};

/** Possible reasons to interrupt an activity. */
enum class distraction_type {
    noise,
    pain,
    attacked,
    hostile_spotted,
    talked_to,
    asthma,
    motion_alarm,
    weather_change,
};

#endif
