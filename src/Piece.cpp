#include "../include/Piece.hpp"

Piece::Piece (int pType) : mType(static_cast<PieceType> (pType)), mRotation(PieceRotation::up), mX(0), mY(0) {}

void Piece::setType (int pType) {
  mType = static_cast<PieceType> (pType);
}

void Piece::setRotation (int pRotation) {
  mRotation = static_cast<PieceRotation> (pRotation);
}

void Piece::movePieceDown (const Board& pBoard) {
  if (pBoard.isCollision (static_cast<int> (mType), static_cast<int> (mRotation), mX, mY + 1) == false) {
    mY += 1;
  }
}

void Piece::movePieceLeft (const Board& pBoard) {
  if (pBoard.isCollision (static_cast<int> (mType), static_cast<int> (mRotation), mX - 1, mY) == false) {
      mX -= 1;
  }
}

void Piece::movePieceRight (const Board& pBoard) {
  if (pBoard.isCollision (static_cast<int> (mType), static_cast<int> (mRotation), mX + 1, mY) == false) {
      mX += 1;
  }
}

void Piece::rotatePiece (const Board& pBoard) {
  if (pBoard.isCollision (static_cast<int> (mType), (static_cast<int> (mRotation) + 1) % 4, mX, mY) == false) {
      switch (mRotation) {
        case PieceRotation::up:
          mRotation = PieceRotation::right; break;
        case PieceRotation::right:
          mRotation = PieceRotation::down; break;
        case PieceRotation::down:
          mRotation = PieceRotation::left; break;
        case PieceRotation::left:
          mRotation = PieceRotation::up; break;
      }
  }
}

void Piece::movePieceBottom (const Board& pBoard) {
  while (pBoard.isCollision (static_cast<int> (mType), static_cast<int> (mRotation), mX, mY + 1) == false) {
    movePieceDown(pBoard);
  }
}