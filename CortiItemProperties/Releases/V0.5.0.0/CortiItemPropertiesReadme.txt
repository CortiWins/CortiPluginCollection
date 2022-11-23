CortiItemProperties DynRPG PlugIn V0.5

 ========== Author: ==========
Corti 23.04.2015 for GhostRider of RMN

 ========== Versionen: ==========
(V0.1) First Version
(V0.2) @get_item_property implemented and tested.
(V0.3) [28.07.2015] Condition and Attribute ID didn't match the database id. Changed from zeroBased to OneBased. DynRPG V0.3 documentation misleads here slightly.
(V0.4) [04.09.2015] Properties "ConditonFlag" and "target" now work. Fixed misleading documentation about parameter order for setting and getting from/to condition and attribute arrays.
(V0.5) [11.09.2015] Made independent from Helper.cpp. Dialog.cpp for message box outputs on errors.

 ========== IMPORTANT: ==========
Unlike all my other plugins which use DynRPG V0.17, this one requires the V0.2 DynLoader as it uses the DynRPG v0.3 Headers and the DynRPG V0.2 Library.

 ========== Purpose: ==========
Set the properties of item in the database via comment-commands.
Those changes are volatile. The database is not saved and loaded when saving and loading savegames.
Changing items affects all items of that type.
Items equipped and in inventory are just id + count, its not possible to change just a single instance of an item.

 ========== Use set_item_property ==========

The command takes 4 parameters for the attributes & conditions-properties.
The command takes 3 parameters for all other properties.

@set_item_property [PropertyName],[ItemId],[SetValue]
@set_item_property "attributes",[ItemId],[attributeId],[SetValue]
@set_item_property "conditions",[ItemId],[conditionId],[SetValue]

[PropertyName] is a string.
[ItemId] is a number.
[SetValue] is a number. For boolean properties, use 1 for true and 0 for false:
[conditionId] is a number. The id in the database.
[attributeId] is a number. The id in the database.

List of properties for items:
http://rewtone.com/dynrpg/class_r_p_g_1_1_item.html

 ========== Use get_item_property ==========
@get_item_property [PropertyName],[ItemId],[VariableId]
@get_item_property "attributes",[attributeId],[ItemId],[VariableId]
@get_item_property "conditions",[conditionId],[ItemId],[VariableId]

[PropertyName] is a string.
[ItemId] is a number.
[VariableId] is a number. The current status is saved ito this variable. Booleans are saved as 1  or 0.
[conditionId] is a number. The id in the database.
[attributeId] is a number. The id in the database.
