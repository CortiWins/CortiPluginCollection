//! Called after a battler was drawn (or supposed to be drawn)
bool onBattlerDrawn ( RPG::Battler *battler, bool isMonster, int id )
{
    CustomCrit::CallbackOnBattlerDrawn(battler, isMonster, id);
    return true;
}
