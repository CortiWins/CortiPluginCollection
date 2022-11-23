//! Called before the first window is drawn. Can be used to draw elements between battlers and before menus.
bool onDrawBattleActionWindow ( int * x, int * y, int selection, bool selActive, bool isVisible)
{
    if(!selActive) // ( 1 )
    {
        CustomCrit::CustomAnimations::DrawCustomAnimationOnOverlay();
        return true;
    }
}
