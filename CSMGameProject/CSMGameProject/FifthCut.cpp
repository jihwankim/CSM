#include "FifthCut.h"
#include "NNApplication.h"

FifthCut::FifthCut()
{
	float width = (float)NNApplication::GetInstance()->GetScreenWidth();
	float height = (float)NNApplication::GetInstance()->GetScreenHeight();

	mBackground = NNSprite::Create( L"Sprite/StoryScene_4.png" );
	mBackground->SetPosition( width/2, height/2 );
	mBackground->SetCenter( mBackground->GetImageWidth()/2.f, mBackground->GetImageHeight()/2.f );
	AddChild( mBackground );

	mStoryTextBox = NNSprite::Create( L"Sprite/StoryTextBox.png");
	mStoryTextBox->SetPosition( width/2, height/2 + 200.f );
	mStoryTextBox->SetCenter( mStoryTextBox->GetImageWidth()/2.f, mStoryTextBox->GetImageHeight()/2.f );
	AddChild( mStoryTextBox );

	mText = NNLabel::Create( L"���� ���ɿ��� �Ǿ� ���� ���ɿ� ��ƿ���ɸ� �����ּ���.\n�Ͼ����, ��翩...", L"���� ���", 20.f );
	AddChild( mText );

	mText->SetPosition( 100.f, 460.f );
	mText->SetBold( true );
}
FifthCut::~FifthCut()
{
}

void FifthCut::Render()
{
	StoryCut::Render();
}
void FifthCut::Update( float dTime )
{
	StoryCut::Update( dTime );
}