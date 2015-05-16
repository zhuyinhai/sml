
#include <algorithm>
#include <fstream>

#include <d3d11_1.h>

#include "test_d3d11/animator.h"
#include "test_d3d11/sprite.h"
#include "test_d3d11/trace.h"

//--------------------------------------------------------------------------------------
// Structures
//--------------------------------------------------------------------------------------
struct Vertex
{
	DirectX::XMFLOAT3 Pos;
	DirectX::XMFLOAT4 Color;
};


struct ConstantBuffer
{
	DirectX::XMMATRIX mWorld;
	DirectX::XMMATRIX mView;
	DirectX::XMMATRIX mProjection;
};


//--------------------------------------------------------------------------------------
// SafeRelease
//--------------------------------------------------------------------------------------
template<typename T>
void safeRelease(T*& obj)
{
	if(nullptr!=obj)
	{
		obj->Release();
	}
	obj = nullptr;
}


// ----------------------
// Animator
// ----------------------
Animator::Animator(void)
	: vertexBuffer_(nullptr)
	, indexBuffer_(nullptr)
	, constantBuffer_(nullptr)
{}

Animator::~Animator(void)
{
	release();
}

bool Animator::initialize(ID3D11Device* device, const char* filepath)
{
	if( !data_.load(filepath) )
	{
		return false;
	}

	auto compItr = data_.getCompositions( [](const sml::data::Composition& data){ return 0==strcmp(data.name, "root"); } );
	if(compItr.isEnd())
	{
		return false;
	}

	Data::Count dataCount;
	data_.count( dataCount, compItr->id );

	sprites_.initialize( dataCount.sprite );
	sprites_.resize(0);
	planes_.initialize( dataCount.plane );
	planes_.resize(0);
	compositions_.initialize( dataCount.composition );
	compositions_.resize(0);
	states_.initialize( dataCount.state );
	states_.resize(0);

	build(*this, *compItr);
	appendStates(*this, compItr->id);

	return setBuffer(device);
}

void Animator::release(void)
{
	safeRelease(vertexBuffer_);
	safeRelease(indexBuffer_);
	safeRelease(constantBuffer_);

	for(auto& sprite : sprites_)
	{
		if( nullptr!= sprite )
		{
			delete sprite;
			sprite = nullptr;
		}
	}
	sprites_.clear();
	for(auto& plane : planes_)
	{
		if( nullptr!= plane )
		{
			delete plane;
			plane = nullptr;
		}
	}
	planes_.clear();
	compositions_.clear();
	states_.clear();
}


void Animator::update(float deltaTime)
{
	auto world = DirectX::XMMatrixTranslation( 100, 30, 0 );
	sml::Composition<SmlConfig>::update( world, deltaTime);
}

void Animator::draw(ID3D11DeviceContext* context)
{
	if(nullptr==context || nullptr==vertexBuffer_ || nullptr==indexBuffer_ || nullptr==constantBuffer_)
	{
		return;
	}

	{
		// Set vertex buffer
		UINT stride = sizeof(Vertex);
		UINT offset = 0;
		context->IASetVertexBuffers(0,1,&vertexBuffer_,&stride,&offset);

		// Set index buffer
		context->IASetIndexBuffer(indexBuffer_,DXGI_FORMAT_R16_UINT,0);

		// Set primitive topology
		context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}

	// Set constant buffer 
	auto world = DirectX::XMMatrixIdentity();
	auto view = DirectX::XMMatrixIdentity();
	auto projection = DirectX::XMMatrixOrthographicOffCenterLH(0.f, 800.f, 600.f, 0.f, 0.f, 1.f );


	ConstantBuffer cb;
	cb.mWorld = XMMatrixTranspose( world );
	cb.mView = XMMatrixTranspose( view );
	cb.mProjection = XMMatrixTranspose( projection );

	UINT offset = 0;
	for(DWORD i=0; i<planes_.size(); ++i)
	{
		planes_[i]->load(world);
		cb.mWorld = XMMatrixTranspose( world );
		context->UpdateSubresource( constantBuffer_, 0, nullptr, &cb, 0, 0 );
		context->VSSetConstantBuffers( 0, 1, &constantBuffer_ );

		context->DrawIndexed( 6, offset, 0 );
		offset += 6;
	}
}

bool Animator::build(Composition& parent, const sml::data::Composition& data)
{
	sml::data::u32 compId = data.id;
	auto itr = data_.getLayers([compId](const sml::data::Layer& layer){ return layer.compositionId==compId; });

	while(!itr.isEnd())
	{
		switch(itr->type)
		{
		case sml::data::LayerType::Composition:
		{
			auto& comp = compositions_.next();
			comp.setName(itr->name);
			comp.setData(&(*itr));
			auto compId = itr->typeId;
			auto compItr = data_.getCompositions( [compId](const sml::data::Composition& c){ return c.id == compId; } );
			if( !compItr.isEnd() )
			{
				build(comp,*compItr);
				appendStates(comp, compItr->id);
				parent.append(comp);
			}
			break;
		}
		case sml::data::LayerType::Plane:
		{
			auto& plane = planes_.next();
			plane = new Plane();
			plane->setName(itr->name);
			plane->setData(&(*itr));

			auto planeId = itr->typeId;
			auto planeItr = data_.getPlanes( [planeId](const sml::data::Plane& p){ return p.id == planeId; } );
			if( !planeItr.isEnd() )
			{
				Plane::Color color;
				color.x = planeItr->color.r;
				color.y = planeItr->color.g;
				color.z = planeItr->color.b;
				color.w = planeItr->color.a;
				plane->setColor( color );
			
				Plane::Size size;
				size.x = planeItr->size.width;
				size.y = planeItr->size.height;
				plane->setSize( size );

				parent.append( *plane );
			}
			break;
		}
		case sml::data::LayerType::Sprite:
		case sml::data::LayerType::NineSliceSprite:
		case sml::data::LayerType::Text:
		case sml::data::LayerType::Mask:
		default:
			break;
		}
		++itr;
	}
	return true;
}

void Animator::appendStates(Composition& comp,sml::data::u32 compId)
{
	auto stateItr = data_.getStates( [compId](const sml::data::State& s){ return s.compositionId == compId; } );
	while(!stateItr.isEnd())
	{
		auto& state = states_.next();
		state.setName(stateItr->name);

		auto stateId = stateItr->id;
		auto getKeyframes = [stateId](const sml::data::StateKeyframe& k){
			return k.stateId == stateId;
		};

		auto kf = data_.getKeyframes(getKeyframes);
		sml::data::Array<sml::data::StateKeyframe> keyframes;
		keyframes.set(&(*kf),data_.countKeyframes(getKeyframes));

		state.setData(&(*stateItr),keyframes);
		comp.append(state);

		++stateItr;
	}
}

bool Animator::setBuffer(ID3D11Device* device)
{
	if(nullptr==device)
	{
		return false;
	}

	safeRelease(vertexBuffer_);
	safeRelease(indexBuffer_);

	assignLayerIndex();
	std::sort(planes_.begin(),planes_.end(),[](const Plane* lhs,const Plane* rhs){ return lhs->getIndex() > rhs->getIndex(); });

	// -------- vertex buffer -------------------- 
	Array<Vertex> vertices;
	vertices.initialize(4 * planes_.size());

	for(DWORD i = 0; i<planes_.size(); ++i)
	{
		auto size = planes_[i]->getSize();
		auto color = planes_[i]->getColor();

		vertices[(4 * i) + 0] = { {0.f, 0.f, 0.f}, color };
		vertices[(4 * i) + 1] = { {size.x, 0.f, 0.f}, color };
		vertices[(4 * i) + 2] = { {0.f, size.y, 0.f}, color };
		vertices[(4 * i) + 3] = { {size.x, size.y, 0.f }, color };
	};
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(Vertex) * vertices.size();
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;
	D3D11_SUBRESOURCE_DATA InitData;
	ZeroMemory(&InitData, sizeof(InitData));
	InitData.pSysMem = vertices.begin();

	auto hr = device->CreateBuffer(&bd, &InitData, &vertexBuffer_);
	if( FAILED(hr) )
	{
		return false;
	}

	// -------- index buffer -------------------- 
	Array<WORD> indices;
	indices.initialize(6 * planes_.size());

	for(WORD i = 0; i<planes_.size(); ++i)
	{
		indices[(6 * i) + 0] = (4 * i) + 0;
		indices[(6 * i) + 1] = (4 * i) + 1;
		indices[(6 * i) + 2] = (4 * i) + 2;
		indices[(6 * i) + 3] = (4 * i) + 2;
		indices[(6 * i) + 4] = (4 * i) + 1;
		indices[(6 * i) + 5] = (4 * i) + 3;
	}
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(WORD) * indices.size();
	bd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	bd.CPUAccessFlags = 0;
	InitData.pSysMem = indices.begin();

	hr = device->CreateBuffer(&bd, &InitData, &indexBuffer_);
	if(FAILED(hr))
	{
		return false;
	}

	// -------- constant buffer -------------------- 
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(ConstantBuffer);
	bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bd.CPUAccessFlags = 0;
    hr = device->CreateBuffer( &bd, nullptr, &constantBuffer_ );
	if(FAILED(hr))
	{
		return false;
	}
	return true;
}


