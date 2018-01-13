# Filler

Filler is a 42 Project to learn about AI.
The goal is to be the last player to put a piece, that can have any size and shape, sent by the Virtual Machine.
To put a piece it needs to overlap ONE player's cell and only ONE and not overlap any of the challengers cells. </br>
Grade : 101%


## Installation
```
$> make && cp rfulop.filler resources/players/
```

## Usage
```
./filler_vm -f [MAP] -p1 [./P1_NAME] -p2 [P2_NAME]
```
Example:
```
$> cd resources && ./filler_vm -f maps/map01 -p1 players/rfulop.filler -p2 players/hcao.filler
```
