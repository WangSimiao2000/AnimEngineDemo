#include <cmath>
#include <cstdio>

#include "raylib.h"

#include "animengine/animengine.h"
#include "animengine/curve.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "AnimEngine Demo");

    // A 3D camera looking at the origin.
    Camera3D camera = {0};
    camera.position = (Vector3){6.0f, 6.0f, 6.0f};  // where the camera sits
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};    // what it looks at
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};        // which way is "up"
    camera.fovy = 45.0f;                            // field of view (degrees)
    camera.projection = CAMERA_PERSPECTIVE;

    // A linear back-and-forth (ping-pong) curve driving the cube on the X axis.
    // Three keyframes form a triangle wave: -3 -> +3 -> -3, all linear. Looping
    // the time with fmod over the period repeats the round trip indefinitely.
    animengine::Curve moveX;
    moveX.addKeyframe(0.0f, -3.0f, animengine::Interpolation::Linear);
    moveX.addKeyframe(2.0f, 3.0f, animengine::Interpolation::Linear);
    moveX.addKeyframe(4.0f, -3.0f);  // last keyframe: interp unused
    const float period = 4.0f;

    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};

    SetTargetFPS(60);

    // Render loop: runs until the window is closed (ESC or close button).
    while (!WindowShouldClose()) {
        // Advance the animation: loop elapsed time within the curve's range.
        const float t = std::fmod(static_cast<float>(GetTime()), period);
        cubePosition.x = moveX.evaluate(t);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
        DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);
        DrawGrid(10, 1.0f);  // ground reference grid
        EndMode3D();

        DrawText(TextFormat("AnimEngine version: %s", animengine::version()), 10, 10, 20, DARKGRAY);
        DrawFPS(screenWidth - 90, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
