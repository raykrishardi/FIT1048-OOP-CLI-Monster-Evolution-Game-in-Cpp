# Monster Evolution Game in C++

# About the project:
This game is one of the three assignments for my FIT1048 (Foundations of C++) unit. The game is designed using object-oriented paradigm, has a command-line interface, and written using Microsoft Visual Studio 2013 IDE. The project folder also contains UML design class diagram and a reflection on my object-oriented design considerations and my justification on how well it was implemented. Below contains the game overview and rules which are directly taken from the assignment brief.

# Game Overview:
You have woken up in a strange dungeon. It is full of weird monsters that you are able to catch and
look after! You will wander the dungeon, finding monsters and evolving them into more powerful
and special versions of themselves. Can you evolve a monster that you can fight against the evil boss
that guards the exit of the dungeon?

# Basic Play:
• The dungeon is a room that is 20 x 10 squares in size (20 wide by 10 high). In “normal”
mode, the player cannot see the contents of a square in the dungeon. In “test” mode, the
player can see the whole dungeon and the contents of each spot.

• The player starts at a random spot along the left hand wall. The exit to the dungeon is at a
random spot on the right hand wall. Your aim is to find the exit.

• In this dungeon are 5 types of monster: “Bugbear”, “Platypie”, “Emoo”, “Octopod”, and
“Skeletor”. The first three monsters are friendly, while the fourth and fifth type are not, and
will attack you. In the dungeon there are 10 of each type of monster, except for “Skeletor”
of which there is only 1, and it is located directly in front of the dungeon exit.

• The player will move around the dungeon. They can move either up, down, left or right. If
they move into the square of a friendly monster they can try to catch it. When five of one
type of monster is caught, it will evolve to a special monster. This is explained below.

• If the player comes across an unfriendly monster, there is a battle, also described below.

• When the player meets the “Skeletor” monster, a battle also takes place, but it is between
an evolved monster and “Skeletor” and is described separately below.

• If the player beats the “Skeletor” monster, then they exit the dungeon and win the game. If
the player is beaten in battle the game is also over and the player loses.

# Players:
The player is represented by the following:

• A name

• A skill level. This is set to 6 at the start of the game.

• A health. This is set to 10 at the start of the game

• A collection of normal monsters

• One (maximum) evolved monster

# Monsters:
Monsters are represented by the following:

• A type

• A skill level. This is set to a random value from 1-3 at the start of the game.

• A health. This is set to a random value from 3-6 at the start of the game.

# Evolved Monsters:
Evolved Monsters are born when 5 of one type of monster has been found and added to a players
collection. These 5 monsters then join up (so are removed from the players collection) and create
one evolved monster. They are represented by the following:

• A type. This is the same as the base monster type.

• A skill level. This is set to the sum of all skill levels from the base monsters.

• A health. This is set to the sum of all health values from the base monsters.

• A special power modifier. This is a number that is added to battles each turn. Its value is 1 if
monster type “Bugbear”, 2 if type “Platypie” or 3 if type “Emoo”.

# “Skeletor”/Boss Monster:
The “Skeletor” monster (the boss monster) is represented by the following:

• A skill level. This is initially set to 10.

• A health. This is initially set to 20.

• A special power modifier. This is a number added to battles each turn. Its value is set to 2.

# Finding a friendly monster:
This describes what happens when the player finds a friendly monster:

• The player must try to “catch” the monster

• To catch the monster, the player generates a random number from 1 to 6. If the number is
equal to or higher than the monsters skill level, the monster has been caught. If not the
monster runs away. If the monster has been caught, it is removed from the dungeon and
goes into the players monster collection. If it runs away, the monster is simply removed from
the dungeon.

• As soon as 5 monsters of the same type are caught, then they immediately change into an
evolved monster. When this happens, a new Evolved Monster is created with the values
described earlier, and the 5 normal monsters are removed from the player’s collection.

• If a player collects 5 of a different type of monster, it will evolve and replace the current
evolved monster.

# Finding an Unfriendly Monster:
This describes what happens when the player finds an unfriendly monster:

• The player must fight the unfriendly monster

• To fight the monster, the player generates a random number between 1 and 6. It is added to
the player’s skill level. Another random number 1-6 is generated for the monster and added
to its skill level. If the player’s total is higher than the monsters total, the monster loses 1
health point. If the monsters total is higher, the player loses a health point. If it is a draw,
neither loses any health. This continues until either the player or monster runs out of health.

# Finding the “Skeletor” Monster:
This describes what happens when the player finds the “Skeletor” monster:

• The player can fight the monster only if they have an Evolved Monster. If they do not have
an evolved monster, the player is returned to their start point of the dungeon.

• To fight the monster, the battle happens between the players Evolved Monster and the
“Skeletor” monster. The player generates a random number between 1 and 6. It is added to
the Evolved Monster’s skill level. Another random number 1-6 is generated for the
“Skeletor” monster and added to its skill level. If the Evolved Monster’s total is higher than
the “Skeletor” monsters total, the “Skeletor” monster loses 1 health point. If the “Skeletor”
monsters total is higher, the Evolved Monster loses a health point. If it is a draw, neither
loses any health. This continues until a monster runs out of health.

• If the Evolved Monster wins, the player has found the exit of the dungeon and the game is
over. They win!

• If the “Skeletor” monster wins, the player is eaten by the monster and they lose!

# Game Modes:
Your game should have two modes that can be chosen at the beginning of your program:
1. Normal Mode – In this mode the game plays as described, with the dungeon hidden from
the player
2. Test Mode – In this mode the game plays as described, with the contents of the dungeon
always shown to the player

# Extra Functionality:
1. The use of Polymorphism
2. Different types of items in the dungeon
  a. There are 3 types of items randomly located in the dungeon
    i. “Cherry”, increase the player health by 1
    ii. “Apple”, increase the player health by 2
    iii. “Melon”, increase the player health by 3
  b. The maximum amount of item generated for each type is a random number between 2 or 3
3. Full data validation
4. Extra coding measures for extra security
