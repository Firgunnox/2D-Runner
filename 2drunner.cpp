#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};


int main()
{
    // WINDOWS DIMENSIONS
    const int windowWidth{512};
    const int windowHeight{380};

    InitWindow(windowWidth, windowHeight, "2D Runner");

    // ACCELERATION DU TO GRAVITY (PIXELS/SECONDS)/SECONDS

    const int gravity{1'000};
  
    // nebula textures
    Texture2D nebula = LoadTexture("textures/nebula.png");

    int nebVel{-200};

    // AnimData for nebula
    AnimData nebData{ 
        {0.0, 0.0, nebula.width/8, nebula.height/8}, // Rectangle rec
        {windowWidth, windowHeight - nebula.height/8}, // Vector2 pos
        0, // int frame
        1.0/12.0, // float updateTime
        0 // float runningTime
    };

    AnimData neb2Data{
        {0.0, 0.0, nebula.width/8, nebula.height/8},
        {windowWidth + 300, windowHeight - nebula.height/8},
        0,
        1.0/16.0,
        0.0
    };

     // scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png");
    AnimData scarfyData;
    scarfyData.rec.width = scarfy.width/6;
    scarfyData.rec.height = scarfy.height;
    scarfyData.rec.x = 0;
    scarfyData.rec.y = 0;
    scarfyData.pos.x = windowWidth/2 - scarfyData.rec.width/2;
    scarfyData.pos.y = windowHeight - scarfyData.rec.height;
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.0/12.0;
    scarfyData.runningTime = 0.0;


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

        if(scarfyData.pos.y >= windowHeight - scarfyData.rec.height )
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

        // UPDATE NEBULA POSITION
        nebData.pos.x += nebVel * dT;

        //UPDATE SECOND NEBULE POSITION

        neb2Data.pos.x += nebVel * dT;

        // UPDATE SCARFY POSITION
        scarfyData.pos.y += velocity * dT;

        // UPDATE SCARFY ANIMATION FRAME
        scarfyData.runningTime += dT;
        if(!isInAir)
        {
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0;
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width;
                scarfyData.frame++;
                if(scarfyData.frame > 5)
                {
                    scarfyData.frame = 0;
                }
            }
        }

        // UPDATE NEBULA ANIMATION FRAME
        nebData.runningTime += dT;
        if(nebData.runningTime >= nebData.updateTime)
        {
            nebData.runningTime = 0.0;
            nebData.rec.x = nebData.frame * nebData.rec.width;
            nebData.frame++;
            if(nebData.frame > 7)
            {
                nebData.frame = 0;
            }
        }
        neb2Data.runningTime += dT;
        if(neb2Data.runningTime >= neb2Data.updateTime)
        {
            neb2Data.runningTime = 0.0;
            neb2Data.rec.x = neb2Data.frame * neb2Data.rec.width;
            neb2Data.frame++;
            if(neb2Data.frame > 7)
            {
                neb2Data.frame = 0;
            }
        }

        DrawTextureRec(nebula, nebData.rec, nebData.pos, WHITE);
        DrawTextureRec(nebula, neb2Data.rec, neb2Data.pos, RED);

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, WHITE);

        // GAME LOGIC ENDS
        EndDrawing();
    }
    UnloadTexture(scarfy);
    UnloadTexture(nebula);

    CloseWindow();
}