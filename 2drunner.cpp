#include "raylib.h"

int main()
{
    // WINDOWS DIMENSIONS
    const int windowsWidth{512};
    const int windowsHeight{380};

    InitWindow(windowsWidth, windowsHeight, "2D Runner");

    // ACCELERATION DU TO GRAVITY (PIXELS/SECONDS)/SECONDS

    const int gravity{1'000};

    // PLAYER TEXTURE
    Texture2D player = LoadTexture("textures/scarfy.png");
    Rectangle playerRec;
    playerRec.width = player.width/6;
    playerRec.height = player.height;
    playerRec.x = 0;
    playerRec.y = 0;
    Vector2 playerPos;
    playerPos.x = windowsWidth/2 - playerRec.width/2;
    playerPos.y = windowsHeight - playerRec.height;

    // IS PLAYER IN THE AIR
    bool isInAir{};

    // JUMP VELOCITY (PIXELS/SECONDS)
    const int jumpgVel{-600};

    int velocity{0};
    
    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        // DELTA TIME (TIME SINCE THE LAST FRAME)

        const float dT{GetFrameTime()};

        // GAME LOGIC BEGINS
        BeginDrawing();
        ClearBackground(WHITE);

        if(playerPos.y >= windowsHeight - playerRec.height )
        {
            // PLAYER IS ON THE GROUND
            velocity = 0;
            isInAir = false;
        }
        else
        {
            // PLAYER IS IN THE AIR
            velocity += gravity * dT;
            isInAir = true;
        }

        // JUMP CHECK
        if(IsKeyPressed(KEY_SPACE) && !isInAir)
        {
            velocity = jumpgVel;
        }

        // UPDATE POSITION
        playerPos.y += velocity * dT;

        DrawTextureRec(player, playerRec, playerPos, WHITE);

        // GAME LOGIC ENDS
        EndDrawing();
    }
    UnloadTexture(player);
    CloseWindow();
}