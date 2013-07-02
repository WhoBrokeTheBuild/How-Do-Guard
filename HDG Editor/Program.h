#pragma once

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Common.h"
#include <ArcApp.h>

#include <IMouseListener.h>
#include <IKeyboardListener.h>

#include "Button.h"
#include "TextButton.h"
#include "Textbox.h"
#include "Dropdown.h"
#include "ImageButton.h"
#include "Label.h"

#include "DataManager.h"

class Program :
    public ArcApp,
    public IMouseListener,
    public IKeyboardListener
{
private:

    Dropdown
        *_pDrpCharacter,
        *_pDrpAnimation;

    TextButton
        *_pBtnFrameLeft,
        *_pBtnFrameRight,
        *_pBtnClearHurt,
        *_pBtnClearAttack,
        *_pBtnToolDrawHurt,
        *_pBtnToolDrawAttack,
        *_pBtnSaveAnimation;

    Label
        *_pLblCurrentFrame;

    vector<string>
        _characters;

    string 
        _currCharacter,
        _currAnim;

    int
        _currFrame;

    Rect
        _workspace,
        _frameRect;

    bool
        _drawingAttack,
        _drawingHurt;

    Vector2 
        _mousePos;

    vector<Vector2>
        _rectPoints;

    map<int, vector<Rect>>
        _currHurtboxes,
        _currAttackboxes;

public:

    static Font
        *spDefaultFont;

    Program(void);
    virtual ~Program(void);

    virtual string toString( void ) const;

    virtual void init( void );
    virtual void term( void );

    virtual void update( const Event& event );
    virtual void render( const Event& event );

    void drpCharacterChanged( const Event& event );
    void drpAnimationChanged( const Event& event );

    void btnFrameLeftClicked ( const Event& event );
    void btnFrameRightClicked( const Event& event );

    void btnClearHurtClicked  ( const Event& event );
    void btnClearAttackClicked( const Event& event );

    void btnToolDrawHurtClicked  ( const Event& event );
    void btnToolDrawAttackClicked( const Event& event );

    void btnSaveAnimationClicked( const Event& event );

    void updateCurrentFrameLabel( void );

    Animation* currentAnimation( void );

    virtual void mouseReleased( const Event& event );
    virtual void mouseMoved   ( const Event& event );

    void addHitboxPoint( Vector2 point );

    void nextFrame( void );
    void prevFrame( void );

    void toggleDrawHurtbox  ( void );
    void toggleDrawAttackbox( void );

    void clearHurtboxes  ( void );
    void clearAttackboxes( void );

    void saveHitboxData( void );

    virtual void keyPressed( const Event& event );
};

#endif