bool onDoBattlerAction ( RPG::Battler * battler, bool  firstTry)
{
    if(!battler->isMonster())
    {
        // Dialog::Show((int)battler->action->_unknown_6, "onDoBattlerAction");
        // Dialog::Show(battler->action->_unknown_14, "onDoBattlerAction");
    }
    CustomCrit::CallbackOnDoBattlerAction(battler);
    return true;
}

bool onBattlerActionDone ( RPG::Battler * battler, bool success )
{
    if(!battler->isMonster())
    {
        // Dialog::Show((int)battler->action->_unknown_6, "onBattlerActionDone");
        // Dialog::Show(battler->action->_unknown_14, "onBattlerActionDone");
    }

    CustomCrit::CallbackOnBattlerActionDone(battler, success);
    return true;
}
