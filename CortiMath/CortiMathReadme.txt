CortiMath DynRPG PlugIn V0.1

 ========== Author: ==========

Original Plugin by:
EN.I ( elsemi.en.i@gmail.com  ) ( 2012 )

Modifications by:
Corti 06.01.14

 ========== Versionen: ==========
(V0.1) Umgebastelter Code von EN.I, atan2 hinzugefügt.

 ========== Zweck und Nutzen: ==========

Berechnet Wurzel, Sinus, Cosinus, Tangens und Atan2.

 ========== Anwendung: ==========

To calculate things, you must use the comment event command. You must type this to
execute the calculation:

@<Command> <argument>, <ID of destination variable>.
==================================================================
Example: @cos 45, 1
==================================================================
The example of avobe calculates the cosine of 45° and stores the result in the
variable [0001]. Of course, you can use Variable pointers to make this plugin
more dynamic, easy and comfortable to use. Just put an V and variable ID to
extract the number of that variable.
===========================
Example: @cos V45, V6
===========================
The example of avobe calculates the cosine of the number stored in the Var [0045]
and stores the result in the variable number stored in the variable [0006]
( V[V[0006]] in simple words).

If any of the commands has bad syntax, this will no execute, or can be cause
an error.

==============================================================================
Command's list.
==============================================================================

 =============  sin =============
It calculates sine of a number.

@sin <degrees>, <ID of destination variable>
The input must be in degress and the result will be multiplied by 1000000.
Example: @sin V1 , 1

 ============= cos  =============
It calculates cosine of a number.

@cos <degrees>, <ID of destination variable>
The input must be in degress and the result will be multiplied by 1000000.
Example: @cos V1 , 1

 ============= tan =============
It calculates tangent of a number.

@tan <degrees>, <ID of destination variable>
The input must be in degress and the result will be multiplied by 1000000.
WARNING: You must know that tan of 45° must not exist. Calculate this will
result in a error. Anyways, i'm not considering this a bug, beacuse it's
a math thing.

Example: @tan V1 , 1

 ============= atan2 =============
Does atan2 calculation.

@atan2 <value>, <ID of destination variable>, <value>
The inputs must be a natural number .
The result will be multiplied by 1000000.

Example: @atan2 V1 , 1, V2

 ============= sqrt =============
It calculates the square root of a number.

@sqrt <number>, <ID of destination variable>
The input must be a natural number and the result will be integrer, floored.
Example: @sqrt V1 , 1

 ========== Verwendung: ==========
 EN.I gab seinen Sourcecode frei, diesem Beispiel folge ich. Macht was ihr wollt damit.

 ========== Probleme / Feedback: ==========
Bei Problemen, Fragen, Rückmeldungen etc. wende dich einfach an mich, den Corti, am besten im RPG-Atelier per Privatnachricht
http://www.multimediaxis.de/members/4806-Corti
