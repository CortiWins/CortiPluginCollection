namespace CustomAnimations
{
// Constants disassembled by KotatsuAkira
//! Number of frames that flashes are shown.
const int FlashFrameCount = 30;
//! Speed of the shake. Values 0-9.
const int AnimShakeSpeed = 4;
//! Strength of the shake. Values 0-9.
const int AnimShakeStrength = 3;
//! Anzahl Frames, die runtergezählt werden.
const int AnimShakeTimerMax = 15;

RPG::Image *flashImagePtr = null;
int flashCounter = FlashFrameCount;

//! Initialize a screen flash. All values are 0 - 31.
void ApplyFlash ( int red, int green, int blue, int magnitude )
{
    flashCounter = 0;
    if ( flashImagePtr == null )
    {
        // Default image is all pixels set to palette[0]. So to color the whole image, setting palette[0] is enough. Nice!
        flashImagePtr = RPG::Image::create ( 320, 240 );
    }

    // animations contain values from 0 to 31 (0001 1111). The RPG value is 0 - 255 (1111 1111). So 31 shifted by 3 bits is ( 1111 1000 ).
    const int ShiftBits = 3;

    flashImagePtr->palette[0] = ( red << ( 16 + ShiftBits ) ) + ( green << ( 8 + ShiftBits )  ) + ( blue << ShiftBits );
    flashImagePtr->applyPalette();
    flashImagePtr->alpha = magnitude << ShiftBits;
}

//! Called in 'onDrawBattleActionWindow' callback when !selActive. Can be used to draw elements between battlers and before menus.
void DrawCustomAnimationOnOverlay()
{
    // The default Screenflash does not work in the Battle-System. Probably because some other animation is overwriting it.
    // This mimics the behaviour by drawing a semitransparent image.
    if ( flashCounter < FlashFrameCount &&  flashImagePtr != null )
    {
        RPG::screen->canvas->draw ( 0, 0, flashImagePtr );
        flashImagePtr->alpha = std::max ( 0, flashImagePtr->alpha - 4 );
        flashCounter++;
    }
}

//! Class to custom-render a RPG::Animation.
class CustomAnimation
{
public:
    //! Reference to the RPG::Animation.
    RPG::Animation *battleAnimation;
    //! Image data of the base animation.
    RPG::Image *imgPtr;
    //! Index of the currently drawn frame.
    int frameIndex;
    //! Number of max. Frames in the Animation.
    int frameMax;
    //! Animations are drawn at 30 FPS. Effects like sound and shakes are only applied at the first call of each frame.
    bool isSecondFrame;
    //! Set if the animation is running.
    bool isEnabled;
    //! Seto to show global effects like Screen-Shake, Screen-Tint and Sounds. Used to make sure that those are not done multiple times when the animation is played in multiple targets.
    bool isGlobalEffectsEnabled;

    //! Initialize a CustomAnimation from an RPG::Animation. animationId = Animation Database ID.
    CustomAnimation ( int animationId )
    {
        imgPtr = null;
        frameIndex = 0;
        isSecondFrame = false;
        isEnabled = false;
        isGlobalEffectsEnabled = false;

        battleAnimation = RPG::battleAnimations[animationId];
        frameMax = battleAnimation->frames.count();

        std::ostringstream filePath;
        filePath << ( battleAnimation->isLargeAnimation ? "battle2/" :  "battle/" ) << battleAnimation->filename << ".png";

        std::ifstream ifile ( filePath.str().c_str() ); // Try to open file for reading
        ifile.close(); // Close stream as file will be opened when loading the file.

        bool fileExists = ( bool ) ifile; // Casted to bool here, so true if ifile != null, i.e. it exists
        if ( fileExists )
        {
            imgPtr = RPG::Image::create();
            imgPtr->useMaskColor = true;
            imgPtr->loadFromFile ( filePath.str() );
        }
    }

    ~CustomAnimation()
    {
        if ( imgPtr != null )
        {
            RPG::Image::destroy ( imgPtr );
            imgPtr = null;
        }
    }

    void Reset()
    {
        frameIndex = 0;
        isSecondFrame = false;
        isEnabled = false;
    }

    //! Apply the animation-effect to target or screen.
    inline void ApplyEffect ( RPG::AnimationEffect *fx, RPG::Battler *battlerPtr )
    {
        if ( isGlobalEffectsEnabled
                && fx->soundEffect != null
                && fx->soundEffect->volume > 0
                && fx->soundEffect->filename.s_str() != "(OFF)" )
        {
            fx->soundEffect->play();
        }

        if ( fx->flashScope == RPG::ANIM_EFFECT_SCOPE_TARGET )
        {
            if ( battlerPtr != null )
            {
                battlerPtr->flash ( fx->red, fx->green, fx->blue, fx->magnitude, FlashFrameCount );
            }
        }
        else if ( isGlobalEffectsEnabled && fx->flashScope == RPG::ANIM_EFFECT_SCOPE_SCREEN )
        {
            // The default Screenflash does not work in the Battle-System. Probably because some other animation is overwriting it.
            // This mimics the behaviour by drawing a semitransparent image.
            CustomAnimations::ApplyFlash ( fx->red, fx->green, fx->blue, fx->magnitude );
        }

        if ( fx->shakeScope == RPG::ANIM_EFFECT_SCOPE_TARGET )
        {
            if ( battlerPtr != null )
            {
                battlerPtr->shakeSpeed = AnimShakeSpeed;
                battlerPtr->shakeStrength = AnimShakeStrength;
                battlerPtr->shakeTimer = AnimShakeTimerMax;
            }
        }
        else if ( isGlobalEffectsEnabled && fx->shakeScope == RPG::ANIM_EFFECT_SCOPE_SCREEN )
        {
            RPG::screen->effect->shakeSpd = 7;
            RPG::screen->effect->shakeStr = AnimShakeStrength;
            RPG::screen->effect->shakeTimer = AnimShakeTimerMax;
        }
    }

    inline void Draw ( int x, int y, RPG::Battler *battlerPtr )
    {
        if ( imgPtr == null || frameIndex >= frameMax )
        {
            return;
        }

        if ( frameIndex < 0 ) // As long as frameIndex in negative, interpret as delayFrames.
        {
            frameIndex++;
            return;
        }

        RPG::AnimationFrame *frame = battleAnimation->frames[frameIndex];
        int sizeFrame = battleAnimation->isLargeAnimation ? 128 : 96;

        int cellCount = frame->cels.count();
        for ( int i = 0; i < cellCount; i++ )
        {
            RPG::AnimationFrameCel *cel = frame->cels[i];
            if ( cel != null && cel->notDeleted )
            {
                int imageSection = cel->imageSection;
                int imageSectionX = imageSection % 5;
                int imageSectionY = imageSection / 5;

                double zoom = cel->magnification / 100.0;
                imgPtr->alpha = ( 100 - cel->transparency ) * 255 / 100;
                RPG::screen->canvas->drawCenteredZoomed (
                    x - cel->xPos,
                    y + cel->yPos,
                    zoom,
                    zoom,
                    imgPtr,
                    imageSectionX * sizeFrame,
                    imageSectionY * sizeFrame,
                    sizeFrame,
                    sizeFrame );
            }
        }

        //! Animations are drawn at 30 FPS. Effects like sound and shakes are only applied at the first call of each frame.
        if ( !isSecondFrame )
        {
            isSecondFrame = true;
            int effectCount = battleAnimation->effects.count();
            for ( int iEffect = 0; iEffect < effectCount; iEffect++ )
            {
                RPG::AnimationEffect *fx = battleAnimation->effects[iEffect];
                if ( fx->startFrame == ( frameIndex + 1 ) )
                {
                    ApplyEffect ( fx, battlerPtr );
                }
            }
        }
        else
        {
            // Second draw of this frame, so next frame.
            frameIndex++;
            isSecondFrame = false;
            if ( frameIndex >= frameMax ) // Last Frame, second call. Animation ended.
            {
                Reset();
            }
        }
    }

    //! Draw the animnation on top of the monster.
    void Draw ( RPG::Monster *monPtr )
    {
        if ( battleAnimation->scope == RPG::ANIM_SCOPE_GLOBAL )
        {
            Draw ( 160, 120, monPtr );
        }
        else
        {
            int y = monPtr->y;
            if ( battleAnimation->yLine == RPG::ANIM_YAXIS_HIGH )
            {
                y -= ( monPtr->image->height >> 1 );
            }
            else if ( battleAnimation->yLine == RPG::ANIM_YAXIS_LOW )
            {
                y += ( monPtr->image->height >> 1 );
            }

            Draw ( monPtr->x, y, monPtr );
        }
    }

    //! Draw the animnation on top of the actor.
    void Draw ( RPG::Actor *actPtr )
    {
        // Character Height Assumptions 80
        const int HeroHeightPx = 80;
        if ( battleAnimation->scope == RPG::ANIM_SCOPE_GLOBAL )
        {
            Draw ( 160, 120, actPtr );
        }
        else
        {
            int y = actPtr->y;
            if ( battleAnimation->yLine == RPG::ANIM_YAXIS_HIGH )
            {
                y -= ( HeroHeightPx >> 1 );
            }
            else if ( battleAnimation->yLine == RPG::ANIM_YAXIS_LOW )
            {
                y += ( HeroHeightPx >> 1 );
            }

            Draw ( actPtr->x, y, actPtr );
        }
    }

    //! Start showing the animation.
    void Start ( int delayFrames, bool showGlobalEffects )
    {
        isGlobalEffectsEnabled = showGlobalEffects;
        frameIndex = -delayFrames;
        isSecondFrame = false;
        isEnabled = true;
    }
};
}
