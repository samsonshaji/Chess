#ifndef MOVE_TYPE_H
#define MOVE_TYPE_H

// Enum for the type of move
//used for move generation and move validation
enum MoveType {
    Normal,
    Capture,
    EnPassant,
    Castling,
    DoublePawn,
    Promotion
};

#endif 
