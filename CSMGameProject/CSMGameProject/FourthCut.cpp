#include "FourthCut.h"
#include "NNApplication.h"

FourthCut::FourthCut()
{
	////////// Window Frame Size //////////
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	////////// Background Image //////////
	mBackground = NNSprite::Create( L"Sprite/StoryScene_3.png" );
	mBackground->SetPosition( width/2, height/2 );
	mBackground->SetCenter( mBackground->GetImageWidth()/2.f, mBackground->GetImageHeight()/2.f );
	AddChild( mBackground );

	////////// Story Text Box //////////
	mStoryTextBox = NNSprite::Create( L"Sprite/StoryTextBox.png");
	mStoryTextBox->SetPosition( width/2, height/2 + 200.f );
	mStoryTextBox->SetCenter( mStoryTextBox->GetImageWidth()/2.f, mStoryTextBox->GetImageHeight()/2.f );
	AddChild( mStoryTextBox );

	////////// Story Text Label //////////
	mText = NNLabel::Create( L"������ ��ƿ���ɴ� ��ȭ�Ǿ�\n ���� ���ɿտ��� ���¸� ���� ������ ���� �ٹӴϴ�.", L"���� ���", 20.f );
	mText->SetPosition( 100.f, 460.f );
	mText->SetBold( true );
	AddChild( mText );
}
FourthCut::~FourthCut()
{

}

void FourthCut::Render()
{
	StoryCut::Render();
}
void FourthCut::Update( float dTime )
{
	StoryCut::Update( dTime );
}