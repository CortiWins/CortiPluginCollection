namespace SplashEffect
{


void Load()
{
    critSymbolImage = RPG::Image::create();
    critSymbolImage->useMaskColor = true;
    critSymbolImage->alpha = 255;
    if(Helper::FileExist("DynRessource\\Splash.png"))
    {
        critSymbolImage->loadFromFile ("DynRessource\\Splash.png", false );
    }
    else
    {
        Dialog::Show("DynRessource\\Splash.png","File does not exist.");
    }
}

void Unload()
{
    RPG::Image::destroy ( critSymbolImage );
    critSymbolImage = null;
}

}
