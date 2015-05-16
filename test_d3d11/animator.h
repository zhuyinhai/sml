
#pragma once 

#include <utility>
#include "test_d3d11/sml_config.h"

#include "test_d3d11/array.h"
#include "test_d3d11/data.h"
#include "test_d3d11/plane.h"


struct ID3D11Device;
struct ID3D11DeviceContext;
struct ID3D11Buffer;

class Sprite;
using Composition = sml::Composition<SmlConfig>;
using State = sml::State<SmlConfig>;


#define MAKE_PATH(...) std::initializer_list<const char*>({ ##__VA_ARGS__ })

// ----------------------
// Animator
// ----------------------
class Animator : public sml::Animator<SmlConfig>
{
public:
	Animator(void);
	virtual ~Animator(void);

	bool initialize(ID3D11Device* device, const char* filepath);
	void release(void);

	void update(float deltaTime);
	void draw(ID3D11DeviceContext* context);

private:
	bool build(Composition& comp, const sml::data::Composition& data);
	void appendStates(Composition& comp, sml::data::u32 compId);

	bool setBuffer(ID3D11Device* device);

private:
	ID3D11Buffer* vertexBuffer_;
	ID3D11Buffer* indexBuffer_;
	ID3D11Buffer* constantBuffer_;

	Array<Sprite*> sprites_;
	Array<Plane*> planes_;
	Array<Composition> compositions_;
	Array<State> states_;

	Data data_;
};
