#include <cstdio>

#include "raylib.h"

#include "aniengine/aniengine.h"

int main() {
    // Verify AniEngine links and works.
    std::printf("AniEngine version: %s\n", aniengine::version());

    // Verify raylib links and works (no window / display needed for this call).
    SetRandomSeed(42);
    std::printf("raylib linked OK, sample random value: %d\n", GetRandomValue(1, 100));

    // The real visual demo (InitWindow / DrawCube driven by aniengine::Curve)
    // will replace this once the curve module exists.
    return 0;
}
