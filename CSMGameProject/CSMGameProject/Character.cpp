#include "Character.h"


CCharacter::CCharacter(void):m_CharacterSprite(NULL)
{
	AnimationImageInfo idleAnimationImageInfo = {2, L"idle",{10.f,10.f}};
	m_AnimationImageInfo.insert( std::map< CharacterState, AnimationImageInfo >::value_type(IDLE,idleAnimationImageInfo));
	
	AnimationImageInfo walkAnimationImageInfo = {2, L"walk",{20.f,10.f}};
	m_AnimationImageInfo.insert( std::map< CharacterState, AnimationImageInfo >::value_type(WALK,walkAnimationImageInfo));
	
	AnimationImageInfo attackAnimationImageInfo = {2, L"attack",{10.f,10.f}};
	m_AnimationImageInfo.insert( std::map< CharacterState, AnimationImageInfo >::value_type(ATTACK,attackAnimationImageInfo));
	
	AnimationImageInfo dieAnimationImageInfo = {2, L"die",{10.f,10.f}};
	m_AnimationImageInfo.insert( std::map< CharacterState, AnimationImageInfo >::value_type(DIE,dieAnimationImageInfo));

	m_AnimationFrameTime = 0.f;
	
	TransState(IDLE);
}

CCharacter::~CCharacter(void)
{
}

void CCharacter::TransState(CharacterState state)
{
	m_CharacterState = state;
	m_AnimationFrameTime = 0;
	m_NowFrame = 0;
	AnimationImageInfo nowAnimationImageInfo = m_AnimationImageInfo.find(m_CharacterState)->second;
	if( m_CharacterSprite != NULL)
	{
		RemoveChild(m_CharacterSprite);
	}
	WCHAR buff[1024];
	swprintf_s(buff,L"Sprite/%s_%d.png",nowAnimationImageInfo.imagePrefix.c_str(),m_NowFrame);
	std::wstring framePath = buff;
	m_CharacterSprite = NNSprite::Create(framePath);
	AddChild(m_CharacterSprite);
}


void CCharacter::Update( float dTime)
{
	//Animation With m_State
	AnimationImageInfo nowAnimationImageInfo = m_AnimationImageInfo.find(m_CharacterState)->second;
	
	//Calculate 'Now Frame' With integration dtime
	m_AnimationFrameTime += dTime;
	bool isFrameChange = false;
	while(nowAnimationImageInfo.frameDelay[m_NowFrame] < m_AnimationFrameTime)
	{
		m_AnimationFrameTime -= nowAnimationImageInfo.frameDelay[m_NowFrame];
		m_NowFrame = (m_NowFrame+1)%nowAnimationImageInfo.totalFrameCount;
		isFrameChange = true;
	}
	if(isFrameChange == true)
	{
		RemoveChild(m_CharacterSprite);
		WCHAR buff[1024];
		swprintf_s(buff,L"Sprite/%s_%d.png",nowAnimationImageInfo.imagePrefix.c_str(),m_NowFrame);
		std::wstring framePath = buff;
		m_CharacterSprite = NNSprite::Create(framePath);
		AddChild(m_CharacterSprite);
	}


	//Check Moving Input, and set Position to move
	if ( NNInputSystem::GetInstance()->GetKeyState( 'A' ) == KEY_DOWN  || 
		NNInputSystem::GetInstance()->GetKeyState( 'A' ) == KEY_PRESSED)
	{
		//Left
		SetPosition( GetPosition() + NNPoint(-10.f,0.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( 'D' ) == KEY_DOWN  || 
		NNInputSystem::GetInstance()->GetKeyState( 'D' ) == KEY_PRESSED)
	{
		//Right
		SetPosition( GetPosition() + NNPoint(10.f,0.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( 'W' ) == KEY_DOWN  || 
		NNInputSystem::GetInstance()->GetKeyState( 'W' ) == KEY_PRESSED)
	{
		//UP
		SetPosition( GetPosition() + NNPoint(0.f,-10.f) * dTime );
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( 'S' ) == KEY_DOWN  || 
		NNInputSystem::GetInstance()->GetKeyState( 'S' ) == KEY_PRESSED)
	{
		//Down
		SetPosition( GetPosition() + NNPoint(0.f,10.f) * dTime );
	}

	if ( NNInputSystem::GetInstance()->GetKeyState( '1' ) == KEY_DOWN )
	{
		TransState(WALK);
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( '2' ) == KEY_DOWN )
	{
		TransState(IDLE);
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( '3' ) == KEY_DOWN )
	{
		TransState(ATTACK);
	}
	if ( NNInputSystem::GetInstance()->GetKeyState( '4' ) == KEY_DOWN )
	{
		TransState(DIE);
	}

	//Change Image By now Frame.
}
void CCharacter::Render()
{
	NNObject::Render();
}