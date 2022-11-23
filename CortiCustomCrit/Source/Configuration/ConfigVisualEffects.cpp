namespace ConfigVisualEffects
{
//! Type of effect that is displayed when a critical strike is executed on a target.
// 1 = SplashEffect. Pops the #include "DynRessource\\Splash.png" graphic on top of the battler.
// 2 = CustomAnimation. Shows an animation, which mimics a battleAnimation with a given database ID.
int visualEffectType = 0;
int visualEffectAnimationDatabaseId = 0;

int delayFramesHeroes = 0;
int delayFramesMonsters = 0;

bool isSplashEffectEnabled;
bool isCustomAnimationEnabled;

void Load()
{
    bool isVisualEffectEnabled = true;
    visualEffectType = Helper::GetValueFromConfig("VisualEffectType");
    if(visualEffectType < 1 || visualEffectType > 2 )
    {
        LOGERROR("VisualEffectType: " << visualEffectType << " Invalid Value. Consult readme for valid settings.");
        isVisualEffectEnabled = false;
    }
    else
    {
        LOGINFO("VisualEffectType: " << visualEffectType);
    }

    if(visualEffectType == 2)
    {
        visualEffectAnimationDatabaseId = Helper::GetValueFromConfig("VisualEffectAnimationDatabaseId");
        if(visualEffectAnimationDatabaseId < 2 || visualEffectAnimationDatabaseId > RPG::battleAnimations.count())
        {
            LOGERROR("VisualEffectAnimationDatabaseId: " << visualEffectAnimationDatabaseId << " Invalid Value. Consult readme for valid settings.");
            isVisualEffectEnabled = false;
        }
        else
        {
             LOGINFO("VisualEffectAnimationDatabaseId: " << visualEffectAnimationDatabaseId);
        }
    }

    delayFramesHeroes = Helper::GetValueFromConfig("DelayFramesHeroes");
    if(delayFramesHeroes < 0)
    {
        LOGERROR("DelayFramesHeroes: " << delayFramesHeroes << " Invalid Value. Consult readme for valid settings.");
        isVisualEffectEnabled = false;
    }
    else
    {
        LOGINFO("DelayFramesHeroes: " << delayFramesHeroes);
    }

    delayFramesMonsters = Helper::GetValueFromConfig("DelayFramesMonsters");
    if(delayFramesMonsters < 0)
    {
        LOGERROR("DelayFramesMonsters: " << delayFramesMonsters << " Invalid Value. Consult readme for valid settings.");
        isVisualEffectEnabled = false;
    }
    else
    {
        LOGINFO("DelayFramesMonsters: " << delayFramesMonsters);
    }

    isSplashEffectEnabled = isVisualEffectEnabled && visualEffectType == 1;
    isCustomAnimationEnabled = isVisualEffectEnabled && visualEffectType == 2;
}
}
