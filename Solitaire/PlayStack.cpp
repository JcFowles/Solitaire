/*
* Bachelor of Software Engineering 
* Media Design School 
* Auckland 
* New Zealand 
 
* (c) 2005 - 2014 Media Design School 
 
* File Name : CPlayStack.cpp
* Description : Implementation file for the PlayStack class
* Author :	JC Fowles

* Mail :	Jc.fowles@mediadesign.school.nz		
*/

// This include
#include "PlayStack.h"

/***********************
* CPlayStack: Contructor for the PlayStack class
* @author: Jc Fowles
********************/
CPlayStack::CPlayStack(void)
{
	m_pCards = new vector<CCard*>;
}

/***********************
* ~CPlayStack: Destructor for the PlayStack class
* @author: Jc Fowles
********************/
CPlayStack::~CPlayStack(void)
{
	while(!m_pCards->empty())
	{
		m_pCards->pop_back();
	}
	delete m_pCards;
	m_pCards = 0;
}

/***********************
* Initialise: Initialises the PlayStack with a blank card to start with
* @author: Jc Fowles
* @parameter: _fX : x position of the playStack
* @parameter: _fY : y position of the playStack
* @return: void
********************/
bool CPlayStack::Initialise(float _fX, float _fY)
{
	CCard* pBlank = new CCard;
	
	pBlank->SetFlipped(true);
	VALIDATE(pBlank->Initialise(SUIT_DEFAULT, ACE));
	pBlank->SetX(_fX);
	pBlank->SetY(_fY);
	//CEntity::SetX(_iX);
	//CEntity::SetY(_iY);
	
	
	m_pCards->push_back(pBlank);

	return (true);

}

/***********************
* Draw: Draws all the cards in the stack
* @author: Callan Moore
* @author: Jc Fowles
* @return: void
********************/
void CPlayStack::Draw()
{
	
	if(m_pCards->size() > 1)
	{

		for(unsigned int i = 1; i < m_pCards->size() ; i++)
		{
			//sets the X value
			(*m_pCards)[i]->SetX((*m_pCards)[i-1]->GetX());
			
			//Sets the Y value based on if its previous card is flipped or not
			if((*m_pCards)[i - 1]->IsFlipped() && ((*m_pCards)[i - 1]->GetSuit() != SUIT_DEFAULT) )
			{
				(*m_pCards)[i]->SetY( ((*m_pCards)[i-1]->GetY()) + 40);
			}
			//
			else
			{
				//sets the first card in the deck to the same position as the blank
				if( i == 1 )
				{
					(*m_pCards)[i]->SetY( ((*m_pCards)[i-1]->GetY()) );
				}
				else
				{
						(*m_pCards)[i]->SetY( ((*m_pCards)[i-1]->GetY()) + 10);
				}
			}
			
			(*m_pCards)[i]->Draw();
		}

	}
	else
	{
		(*m_pCards)[0]->Draw();
	}
	
}

/***********************
* Process: Process the card stack
* @author: Jc Fowles
* @parameter: _fDeltaTick: How long it takes to do the procces
* @return: void
********************/
void CPlayStack::Process(float _fDeltaTick)
{
	//FlipCard();
}

/***********************
* AddCards: Adds cards to the card play stack
* @author: Jc Fowles
* @parameter: _pCards: Vector of cards to add to the stack
* @return: bool : True if cards were added, False if not
********************/
bool CPlayStack::AddCards(vector<CCard*>* _pCards)
{
	if( (CardCheckSuit((*_pCards)[0])) ||
		(BlankCheck((*_pCards)[0]))     )
	{
		for(unsigned int i = 0 ; i < _pCards->size() ; i++)
		{
			m_pCards->push_back((*_pCards)[i]);
		}
		return true;
	}
	else 
	{
		return false;
	}
}

/***********************
* RemoveCards: Remove cards to the card play stack
* @author: Jc Fowles
* @parameter: _pCards: Vector of cards to remove from the stack
* @return: bool : True if cards were removed, False if not
********************/
vector<CCard*>* CPlayStack::RemoveCards(int _iCardFromTop)
{
	vector<CCard*>* pCardsToRemove = 0;

	for(unsigned int i = _iCardFromTop; i < m_pCards->size() ; i++)
	{
		pCardsToRemove->push_back((*m_pCards)[i]);
	}

	//remove from the play stack
	for(int i = m_pCards->size(); i > _iCardFromTop; i--)
	{
		m_pCards->pop_back();
	}

	return pCardsToRemove;
}

/***********************
* CardCheck: Checks if cards can be added to stack, based on if its a red card on black or vice versa
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CPlayStack::CardCheckSuit( CCard*  _kpCard)
{
	
	if( ((_kpCard->GetSuit()) < 2) &&
		((*m_pCards).back()->GetSuit() > 1) )
	{
		return CardCheckValue(_kpCard);
	}
	else if( ((_kpCard->GetSuit()) > 1) &&
			 ((*m_pCards).back()->GetSuit() < 2) )
	{
		return CardCheckValue(_kpCard);
	}
	else
	{
		return false;
	}

}

/***********************
* FlipCard: Flips the top card if it is not visible
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if card has been flipped, False if not
********************/
bool CPlayStack::FlipCard()
{
	if(!((*m_pCards).back()->IsFlipped()))
	{
		(*m_pCards).back()->SetFlipped(true);
	}
	
	return true;

}

/***********************
* CardCheckValue: Checks if cards can be added to stack, based on its value
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CPlayStack::CardCheckValue( CCard*  _kpCard)
{
	if( (_kpCard->GetNumber()) == (((*m_pCards).back()->GetNumber()) - 1) )
	{
		return true;
	}
	return false;
}

/***********************
* BlackCheck: Checks if cards can be added to stack, based on its value
* @author: Jc Fowles
* @parameter: _kpCard: constant pointer to a constant card, to be checked
* @return: bool : True if cards can be added, False if not
********************/
bool CPlayStack::BlankCheck( CCard*  _kpCard)
{
	if( ((_kpCard->GetNumber()) == KING ) &&
		(((*m_pCards).back()->GetSuit()) == SUIT_DEFAULT))
	{
		return true;
	}
	else
	{
		return false;
	}
}

/***********************
* SetStack: Sets the stack to the passed in stack only used when adding the first initial stack
* @author: Jc Fowles
* @parameter: _InitialStack: pointer to vector of cards pointers to set the play Stack to 
* @return: void
********************/
void CPlayStack::SetStack(vector<CCard*>* _InitialStack)
{
	m_pCards = _InitialStack;
}

/***********************
* getStack: Returns the play stack in the form of a pointer to a vector of card pointers
* @author: Jc Fowles
* @return: vector<CCard*>* : a pointer to a vector of card pointers, which is the stack
********************/
vector<CCard*>* CPlayStack::GetStack()
{
	return m_pCards;
}
