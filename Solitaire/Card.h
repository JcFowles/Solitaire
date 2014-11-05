/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : Backbuffer.h
* Description : Header file for the Backbuffer class
* Author :	Callan Moore
*			JC Fowles
*			Nick Gould
* Mail :	Callan.moore@mediadesign.school.nz
*			Jc.fowles@mediadesign.school.nz	
*			Nick.gould@mediadesign.school.nz
*/

#pragma once


#if !defined(__CARD_H__)
#define __CARD_H__

// Library Includes

// Local Includes
#include"Utilities.h"
#include "Entity.h"
#include "resource.h"

// Prototypes
class CCard : public CEntity
{
public:
	CCard(void);
	~CCard(void);

	virtual bool Initialise(ESuit, ECardNum);
	virtual void Draw();
	virtual void Process(float _fDeltaTick);

	ESuit GetSuit();
	ECardNum GetNumber();
	bool IsVisible();

	void SetSuit(ESuit _eSuit);
	void SetNumber(ECardNum _eCardNum);
	void SetVisible(bool _bIsVisible);

protected:
	ESuit m_eSuit;
	ECardNum m_eCardNum;
	bool m_bIsVisible;

private:
	int m_iSpriteID_X;
	int m_iSpriteID_Y;
	int m_iMaskID;
};




#endif // __CARD_H__