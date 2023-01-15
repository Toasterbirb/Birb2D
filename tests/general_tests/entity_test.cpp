#include "doctest.h"
#include "BaseEntity.hpp"

using namespace Birb;

namespace BirbTest
{
	TEST_CASE("Entity comparison")
	{
		BaseEntity entityA("First entity");
		CHECK(entityA == entityA);

		BaseEntity entityB("Second entity");
		CHECK_FALSE(entityA == entityB);
		entityB.name = "First entity";
		CHECK_FALSE(entityA == entityB);
	}

	TEST_CASE("Empty entity")
	{
		BaseEntity entity;
		CHECK(entity.name == "Default Entity");
	}

	// TODO: Re-make these tests in separate files testing one entity
	// at a time

	//TEST_CASE("Use an uninitialized font in a text component")
	//{
	//	Font font;
	//	Entity entity("Text entity",
	//			Vector2Int(0, 0),
	//			EntityComponent::Text("Some text", &font, &Colors::White));
	//}

	//TEST_CASE("Entity with a custom rendering priority")
	//{
	//	Entity entityA("Rect entity", Rect(0, 0, 0, 0), 4);
	//	CHECK(entityA.renderingPriority == 4);

	//	Texture empty_texture;

	//	Entity entityB("Entity with a texture", Rect(0, 0, 10, 10), empty_texture, 4);
	//	CHECK(entityB.renderingPriority == 4);

	//	Entity entityC("Entity with a texture2", Vector2Int(0, 0), empty_texture, 4);
	//	CHECK(entityC.renderingPriority == 4);

	//	EntityComponent::Animation animation;
	//	Entity entityD("Entity with an animation component", Vector2Int(1, 2), empty_texture, animation, 4);
	//	CHECK(entityD.renderingPriority == 4);

	//	EntityComponent::Text text;
	//	Entity entityE("Entity with a text component", Vector2Int(4, 4), text, 4);
	//	CHECK(entityE.renderingPriority == 4);
	//}
}
