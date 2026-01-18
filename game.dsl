entity Player
    has health 100
    has speed 200

entity Enemy
    has health 30

when Player collides Enemy
    Enemy health -= 10