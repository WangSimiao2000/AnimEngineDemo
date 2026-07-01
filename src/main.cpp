// ============================================================================
//  AnimEngineDemo — Tween vs Spring
// ----------------------------------------------------------------------------
//  Two balls chase the SAME target on the X axis. Press SPACE to flip the
//  target between left and right and watch how each animation model reacts:
//
//    RED  ball  -> Tween  : fixed-duration easing. Re-targeting mid-flight
//                           has to RESTART the animation (a visible snap).
//    BLUE ball  -> Spring : physics-based. Re-targeting keeps the current
//                           velocity and smoothly redirects (no restart).
//
//  Everything tagged with the "AnimEngine API" banners below is the library
//  surface being demonstrated. Everything else is raylib setup / rendering
//  boilerplate and is intentionally kept out of the way.
// ============================================================================

#include "raylib.h"

#include "animengine/spring.h"
#include "animengine/tween.h"

using animengine::Easing;
using animengine::Spring;
using animengine::Tween;

// ----------------------------------------------------------------------------
// Demo configuration (tweak these to change the feel)
// ----------------------------------------------------------------------------
namespace {
constexpr int kScreenWidth = 900;
constexpr int kScreenHeight = 600;

constexpr float kLeftX = -5.0f;
constexpr float kRightX = 5.0f;
constexpr float kBallRadius = 0.6f;

// Tween: how long each move takes, and which easing curve to use.
constexpr float kTweenDuration = 1.0f;
constexpr Easing kTweenEasing = Easing::EaseInOut;

// Spring: duration ~ how fast it responds, bounce ~ how springy (0 = no bounce).
constexpr float kSpringDuration = 0.6f;
constexpr float kSpringBounce = 0.4f;
}  // namespace

// ----------------------------------------------------------------------------
// raylib boilerplate — NOT part of AnimEngine.
// ----------------------------------------------------------------------------
static Camera3D makeCamera() {
    Camera3D camera = {0};
    camera.position = Vector3{0.0f, 6.0f, 16.0f};
    camera.target = Vector3{0.0f, 1.0f, 0.0f};
    camera.up = Vector3{0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    return camera;
}

int main() {
    // ===== SETUP (boilerplate) ==============================================
    InitWindow(kScreenWidth, kScreenHeight, "AnimEngine Demo - Tween vs Spring");
    SetTargetFPS(60);
    const Camera3D camera = makeCamera();

    float target = kRightX;  // the shared destination both balls aim for

    // ┌──────────────────────────────────────────────────────────────────────┐
    // │  AnimEngine API — create the two animations                            │
    // └──────────────────────────────────────────────────────────────────────┘
    // Tween: interpolate from -> to over a fixed duration using an easing curve.
    Tween tween(kLeftX, target, kTweenDuration, kTweenEasing);

    // Spring: construct at rest at kLeftX, then aim it at the target.
    Spring spring(kSpringDuration, kSpringBounce, kLeftX);
    spring.setTarget(target);
    // ────────────────────────────────────────────────────────────────────────

    while (!WindowShouldClose()) {
        const float dt = GetFrameTime();

        // ----- Input: flip the shared target on SPACE (boilerplate) ---------
        if (IsKeyPressed(KEY_SPACE)) {
            target = (target == kRightX) ? kLeftX : kRightX;

            // ┌────────────────────────────────────────────────────────────┐
            // │  AnimEngine API — re-target                                  │
            // └────────────────────────────────────────────────────────────┘
            // Tween has no concept of momentum: to chase a new target we must
            // build a fresh tween starting from the current position.
            tween = Tween(tween.value(), target, kTweenDuration, kTweenEasing);

            // Spring just changes its target; it keeps its current velocity
            // and smoothly redirects — no restart.
            spring.setTarget(target);
            // ──────────────────────────────────────────────────────────────
        }

        // ┌──────────────────────────────────────────────────────────────────┐
        // │  AnimEngine API — advance the animations and read their values     │
        // └──────────────────────────────────────────────────────────────────┘
        tween.update(dt);
        spring.update(dt);

        const float tweenX = tween.value();
        const float springX = spring.value();
        // ────────────────────────────────────────────────────────────────────

        // ===== RENDER (boilerplate) ========================================
        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawGrid(20, 1.0f);

        // Faint marker showing where the shared target currently is.
        DrawCube(Vector3{target, 1.0f, 0.0f}, 0.1f, 3.0f, 4.5f, LIGHTGRAY);

        DrawSphere(Vector3{tweenX, 1.0f, -2.0f}, kBallRadius, RED);    // Tween ball
        DrawSphere(Vector3{springX, 1.0f, 2.0f}, kBallRadius, BLUE);   // Spring ball
        EndMode3D();

        // HUD
        DrawText("Press SPACE to flip the target", 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("RED  Tween  (EaseInOut, %.1fs)   x = %+.2f", kTweenDuration, tweenX),
                 10, 42, 18, RED);
        DrawText(TextFormat("BLUE Spring (bounce %.1f)         x = %+.2f   v = %+.2f",
                            kSpringBounce, springX, spring.velocity()),
                 10, 64, 18, BLUE);
        DrawText("Tween restarts on each flip; Spring keeps its momentum.", 10,
                 kScreenHeight - 30, 18, DARKGRAY);

        DrawFPS(kScreenWidth - 90, 10);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
