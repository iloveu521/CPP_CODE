#ifndef _PIECES_H
#define _PIECES_H

//--------------------------------
//Pieces
//--------------------------------

class Pieces {
public :
	int GetBlockType(int pPiece, int pRotation, int pX, int pY);
	int GetXInitialPosition(int pPiece, int pRotation);
	int GetYInitialPosition(int pPiece, int pRotation);
};

#endif //_PIECES_H
