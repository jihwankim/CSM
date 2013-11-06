
#include "NNObject.h"



NNObject::NNObject()
	: m_pParent(nullptr),
	m_Position(0.f,0.f), m_Center(0.f,0.f), m_AnchorPoint(0.f,0.f),
	m_ScaleX(1.f), m_ScaleY(1.f), m_Rotation(0.f), m_Zindex(0),
	m_Visible(true)
{
}
NNObject::~NNObject()
{
	for (auto& iter=m_ChildList.begin(); iter!=m_ChildList.end(); iter++ )
	{
		SafeDelete( *iter );
	}
	m_ChildList.clear();
}

void NNObject::Render()
{
	if ( m_Visible == false ) return;

	
	m_Matrix = D2D1::Matrix3x2F::Translation( m_Position.GetX(), m_Position.GetY() ) *
		D2D1::Matrix3x2F::Rotation( m_Rotation, D2D1::Point2F((m_Position+m_Center).GetX(), (m_Position+m_Center).GetY()) ) *
		D2D1::Matrix3x2F::Scale( m_ScaleX, m_ScaleY, D2D1::Point2F((m_Position+m_Center).GetX(), (m_Position+m_Center).GetY()) );

	m_Matrix.TransformPoint( D2D1::Point2F( m_AnchorPoint.GetX(), m_AnchorPoint.GetY() ) );

	if( m_pParent )
	{
		m_Matrix = m_Matrix * m_pParent->GetMatrix();
	}

	// 	for (auto& iter=m_ChildList.begin(); iter!=m_ChildList.end(); iter++ )
	// 	{
	// 		(*iter)->Render();
	// 	}
	for (const auto& child : m_ChildList )
	{
		child->Render();
	}
}
void NNObject::Update( float dTime )
{
	if ( m_Visible == false ) return;

	// 	for (auto& iter=m_ChildList.begin(); iter!=m_ChildList.end(); iter++ )
	// 	{
	// 		(*iter)->Update( dTime );
	// 	}
	for (const auto& child : m_ChildList)
	{
		child->Update( dTime );
	}
}
void NNObject::SortingChildByZindex()
{
	m_ChildList.sort([](const NNObject* object1, const NNObject* object2) -> bool {
		return object1->GetZindex() < object2->GetZindex();
	});
}
void NNObject::AddChild( NNObject* object )
{
	object->SetParent( this );

	m_ChildList.push_back( object );
	SortingChildByZindex();
}
void NNObject::AddChild( NNObject* object, int zindex )
{
	object->SetParent( this );
	object->SetZindex( zindex );
	m_ChildList.push_back( object );
	SortingChildByZindex();
}
void NNObject::RemoveChild( NNObject* object, bool memoryDel )
{
	for (auto& iter=m_ChildList.begin(); iter!=m_ChildList.end(); iter++ )
	{
		if ( (*iter) == object )
		{
			if ( memoryDel == true )
			{
				SafeDelete( *iter );
			}
			m_ChildList.erase( iter );
			break;
		}
	}
}


