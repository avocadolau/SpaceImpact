#include "ScreenLogo.h"
#include "raylib.h"

ScreenLogoState::ScreenLogoState()
	: chargeTime_(0)
{}

ScreenLogoState& ScreenLogoState::getInstance()
{
    static ScreenLogoState singleton;
    return singleton;
}

//-------------------------------------------------------------
void ScreenLogoState::InitScreen(void)
{
    framesCounter = 0;

    logoPositionX = GetScreenWidth() / 2 - 128;
    logoPositionY = GetScreenHeight() / 2 - 128;

    //state = 0;
    //alpha = 1.0f;

    text = "Made by Laura I.";
    Image customLogo = LoadImage("resources/customLogo.jpg");
    ImageResize(&customLogo, customLogo.width / 4, customLogo.height / 4);
    logoTex = LoadTextureFromImage(customLogo);
    UnloadImage(customLogo);
}

//-------------------------------------------------------------
void ScreenLogoState::UpdateScreen(float deltaTime)
{
#ifdef WIP_LOGO
    
    
    framesCounter++;


    //alpha += 1 / (TextLength(text) * 4);
    //if (state != 4) state == 4;

    if (state == 0)
    {
        textCount = framesCounter / 4;
        alpha += 0.02f;
        if (textCount >= TextLength(text))
        {
            state = 1;
            alpha = 1;
            framesCounter = 0;
        }
    }
    else if (state == 1)
    {
        if (framesCounter == 30) {
            state = 2;
            framesCounter = 0;
        }
    }
    else if (state == 2)
    {
        alpha -= 0.02f;
        if (alpha <= 0.0f)
                {
                    alpha = 0.0f;
                    finishScreen = 1;   // Jump to next screen
                }
    }

#endif // WIP_LOGO



}

//-------------------------------------------------------------
void ScreenLogoState::DrawScreen(void)
{
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), WHITE);



    // -----------------
#ifdef WIP_LOGO
    
    
    if (state == 0)
    {
        const char* displayText = TextSubtext(text, 0, textCount);
        DrawText(displayText, logoPositionX, logoPositionY - 27, 20, DARKGRAY);
    }
    else if (state ==1)
    {
        DrawText(text, logoPositionX, logoPositionY - 27, 20, DARKGRAY);
    }
    else DrawText(text, logoPositionX, logoPositionY - 27, 20, Fade(DARKGRAY,alpha));
    DrawTexture(logoTex, GetScreenWidth() / 2 - logoTex.width / 2, GetScreenHeight() / 2 - logoTex.height / 2, Fade(WHITE, alpha));


    //DrawTexture(logoTex, GetScreenWidth() / 2 - logoTex.width / 2, GetScreenHeight() / 2, Fade(WHITE, alpha));

#endif // WIP_LOGO
    
    
}

//-------------------------------------------------------------
void ScreenLogoState::UnloadScreen(void)
{

}

//-------------------------------------------------------------
int  ScreenLogoState::FinishScreen(void)
{
    return finishScreen;
}