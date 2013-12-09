
#include "SecondCut.h"
#include "NNApplication.h"

SecondCut::SecondCut()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	mBackground = NNSprite::Create( L"Sprite/StoryScene_1.png" );
	mBackground->SetPosition( width/2, height/2 );
	mBackground->SetCenter( mBackground->GetImageWidth()/2.f, mBackground->GetImageHeight()/2.f );
	AddChild( mBackground );

	mStoryTextBox = NNSprite::Create( L"Sprite/StoryTextBox.png");
	mStoryTextBox->SetPosition( width/2, height/2 + 200.f );
	mStoryTextBox->SetCenter( mStoryTextBox->GetImageWidth()/2.f, mStoryTextBox->GetImageHeight()/2.f );
	AddChild( mStoryTextBox );

	mText = NNLabel::Create( L"���ɵ��� ���ɿ��� �̾� �ڿ��� ��Ģ�� �����ϵ��� �ϰ� �ִ���.", L"���� ���", 20.f );
	AddChild( mText );

	mText->SetPosition( 100.f, 460.f );
	mText->SetBold( true );
}
SecondCut::~SecondCut()
{

}

void SecondCut::Render()
{
	StoryCut::Render();
}
void SecondCut::Update( float dTime )
{
	StoryCut::Update( dTime );
}