#ifndef OBJECT_H
#define OBJECT_H

#include <stdexcept>
#include <cassert>
#include <functional>
#include <iostream>
#include <set>

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>

#include "animation.h"
#include "hud.h"
#include "music.h"

namespace GameSpace
{
	//////////////////////////////////////////////////////////////////////////
	class Object
	{
		sf::Texture m_texture;
		sf::Sprite m_sprite;
	protected:
		sf::Texture& getTexture();
		sf::Sprite& getSprite();
		/*
			@brief ������� ������� ������
			@param source ����������� ��������
			@param centerX ��������� ������ ������� �� �
			@param centerY ��������� ������ ������� �� �
			@param frameX �������� � ����������� �� �
			@param frameY �������� � ����������� �� �
			@param frameWidth ������ ����� � �����������
			@param frameHeight ������ ����� � �����������
		*/
		Object(	const sf::Image& source, int centerX, int centerY, 
				int frameX, int frameY, int frameWidth, int frameHeight);
		/*
			@brief �������� ������
		*/
		Object(const Object& other);
		/*
			@brief ����������� ������
		*/
		Object& operator=(const Object& other);
	public:
		/*
			@brief ����� ����� ������������
		*/
		virtual ~Object() = default;
		/*
			@brief ������������ ������
			@param render ������ � ������� ����� ���������
		*/
		virtual void draw(sf::RenderWindow& render);
		/*
			@brief �������� ��������� �������� (�� ��������� ����)
			@param delta ����� ����� � ��������
		*/
		virtual void animate(float delta);
		/*
			@brief �������� ��������� ������ ��� ��������, � ������� ��� ����
			@param delta ����� ����� � ��������
		*/
		virtual void logic(float delta);
		/*
			@brief ���������� �������� ��������� ������ � �������� ����������� ������
			@param live ������ �� �����
			@param coin ������ �� ������
		*/
		virtual void effect(int live, int coin);
		/*
			@brief	������������ ��� ����������� ��������, ���� ��� ���������� � ������ ����
			@ret	������� �� ������� ������ �� ������� ��������
		*/
		virtual bool destroy();
	};
	//////////////////////////////////////////////////////////////////////////
	class PhysicObject : public Object
	{
		b2Body* m_body;
	protected:
		b2Body*& getBody();
		static const double DEGTORAD;
		static const double RADTODEG;
		/*
			@brief ����������� ������� � ���.�������
		*/
		static float mapPixelToPhysic(float v);
		static float mapPixelToPhysic(int v);
		/*
			@brief ����������� ���.������� � �������
		*/
		static float mapPhysicToPixel(float v);
		/*
			@brief ���������� �������� ������� � �������� Object
			@param ��� ��������� �� �������� ������ Object
		*/
		PhysicObject(	const sf::Image& source, int centerX, int centerY,
						int frameX, int frameY, int frameWidth, int frameHeight);
		/*
			@brief ���������� ����������� ����������
		*/
		PhysicObject(const PhysicObject& other) = default;
		PhysicObject& operator=(const PhysicObject& other) = default;
	public:
		/*
			@brief	���������, ������� �������� ������������ ������� ��� ������������
					����� ������ ��� ��������, ������� ����� ������
		*/
		struct Collision
		{
			// ������� ������
			PhysicObject* m_mainObject;
			// ��������� ��� �������
			enum class PhysicObjectType{	POT_UNDEF, 
											POT_HARD, 
											POT_MOVE, 
											POT_PLAYER, 
											POT_SENSOR, 
											POT_PLATFORM,
											POT_JUMPER,
											POT_EFFECT} m_mainObjectType;
			// �������, ���������� ��� ������������
			// �������� - ������ Collision
			std::function<void(Collision*)> m_onCollide;
			// �������, ���������� ��� ����� �� ������������
			// �������� - ������ Collision
			std::function<void(Collision*)> m_onUnCollide;
		};
		Collision m_objectCollision;	// ������������ ��� ������������ � ��������
		/*
			@brief ����������� ����������
		*/
		virtual ~PhysicObject() = default;
		/*
			@brief ��������� ������� � ������������ � ������������ � ����
			@param render ����� ��� ���������
		*/
		virtual void draw(sf::RenderWindow& render) override;
	};
	//////////////////////////////////////////////////////////////////////////
	class SimpleObject : public Object
	{
	public:
		/*
			@brief ������� ���������
			@param ��� ��������� �� �������� ������ Object
		*/
		SimpleObject(	const sf::Image& source, int centerX, int centerY,
						int frameX, int frameY, int frameWidth, int frameHeight);
		/*
			@brief ������� ��������� �� ������ �����������
			@param source �������� �����������
			@param centerX ��������� ������ �� �
			@param centerY ��������� ������ �� Y
		*/
		SimpleObject(const sf::Image& source, int centerX, int centerY);
		/*
			@brief ����� ����������
		*/
		SimpleObject(const SimpleObject& other) = default;
		SimpleObject& operator=(const SimpleObject& other) = default;
		virtual ~SimpleObject() = default;
	};
	//////////////////////////////////////////////////////////////////////////
	class HardObject : public PhysicObject
	{
	public:
		/*
			@brief ������� "������" ������ ���� - �� ��������� � �� ��������
			@param ��� ��� � �������� +
			@param world ��� ������
			@param friction ���������� ������
		*/
		HardObject(	const sf::Image& source, int centerX, int centerY,
					int frameX, int frameY, int frameWidth, int frameHeight,
					b2World* world, float friction);
		/*
			@brief ������� "������" ������ ���� �������� � ������
		*/
		HardObject(const sf::Image& source, int centerX, int centerY, b2World* world, float friction);

		HardObject(const HardObject& other) = default;
		HardObject& operator=(const HardObject& other) = default;
		virtual ~HardObject() = default;
	};
	//////////////////////////////////////////////////////////////////////////
	// ������������ ��� �������� ���������� ��������
	class PlatformObject : public PhysicObject
	{
		b2Vec2 m_srcPoint;	// ����� �������� ������
		b2Vec2 m_dstPoint;	// ����� �������� ����������
		float m_speed;
	public:
		/*
			@brief ������� ���������, ��������������
					�� (centerX, centerY) � (dstCenterX, dstCenterY)
			@param ��� ��� � �������� +
			@param dstCenterX ���������� ���������� �
			@param dstCenterY ���������� ���������� �
			@param friction ���������� ������ ������� ����� ������
			@param speed �������� �������� ���������
		*/
		PlatformObject(	const sf::Image& source, int centerX, int centerY,
						int frameX, int frameY, int frameWidth, int frameHeight,
						b2World* world, int dstCenterX, int dstCenterY,
						float friction, float speed);

		PlatformObject(const PlatformObject&) = default;
		PlatformObject& operator=(const PlatformObject&) = default;
		virtual ~PlatformObject() = default;

		/*
			@brief ������ ���������
		*/
		void logic(float delta) override;
	};
	//////////////////////////////////////////////////////////////////////////
	// ������������ ��� �������� ��������� �����������
	class JumpingObject : public PhysicObject
	{
	public:
		/*
			@brief ������� ������, �� ������� ����� �������
			@param ��� ��� � �������� +
			@param friction ���������� ������ ������� ������
			@param restitution ���������� ���������
		*/
		JumpingObject(const sf::Image& source, int centerX, int centerY,
			int frameX, int frameY, int frameWidth, int frameHeight,
			b2World* world, float friction, float restitution);

		JumpingObject(const JumpingObject&) = default;
		JumpingObject& operator=(const JumpingObject&) = default;
		virtual ~JumpingObject() = default;
	};
	//////////////////////////////////////////////////////////////////////////
	// ������������ ��� ������, ������� � �������� �������� � �������
	class EffectObject : public PhysicObject
	{
		int m_liveEffect;	// ������, ����������� �����
		int m_coinEffect;	// ������, ����������� �������
		bool m_isDestroyable;	// ���������� ����� �������
		bool m_selfDestroy;	// ������ ������ �����������
		std::set<PhysicObject*> m_contacts;	// ����������� ��������, ����� ��������� ������ ������ �����
		/*
			@brief ���������� ����� �������� � ��������
			@param other ������, � ������� ��������� �������
		*/
		void onCollision(PhysicObject::Collision* other);
		/*
			@brief ���������� ����� ����������� �������� � ��������
			@param other ������, � ������� ������� �������
		*/
		void onUnCollision(PhysicObject::Collision* other);
	public:
		/*
			@brief ������� ������ ������� �������
			@param ��� ��� � �������� +
			@param friction ���������� ������
			@param restitution ���������� ��������� (����������� ����� �����)
			@param liveEffect ������, ����������� ����� ��� �������
			@param coinEffect ������, ����������� ������� ��� �������
			@param isDestroyable ���������� ������ ����� ������� � ���
		*/
		EffectObject(	const sf::Image& source, int centerX, int centerY,
						int frameX, int frameY, int frameWidth, int frameHeight,
						b2World* world, float friction, float restitution, 
						int liveEffect, int coinEffect, bool isDestroyable	);

		EffectObject(const EffectObject&) = default;
		EffectObject& operator=(const EffectObject&) = default;
		virtual ~EffectObject() = default;

		virtual bool destroy() override;
	};
	//////////////////////////////////////////////////////////////////////////
	// ������������ ��� ������ � ������ ���������, ������� ����� ���������
	class MoveObject : public PhysicObject
	{
	public:
		/*
			@brief ������� ������ ����, ��������� � �����������
			@param ��� ��� � �������� +
			@param density ��������� (�� ����� ������� �����)
			@param friction ���������� ������
		*/
		MoveObject(	const sf::Image& source, int centerX, int centerY,
					int frameX, int frameY, int frameWidth, int frameHeight,
					b2World* world, float density, float friction);

		MoveObject(const MoveObject& other) = default;
		MoveObject& operator=(const MoveObject& other) = default;
		virtual ~MoveObject() = default;
	};
	//////////////////////////////////////////////////////////////////////////
	class PlayerObject : public MoveObject
	{
		int m_numFootContact; // ���������� ��������� � ������
		/*
			@brief ���������� ��� �������� � �������� ������ ������
			@param other ������, � ������� ����������� �������
		*/
		void onFootSensorCollision(PhysicObject::Collision* other);
		/*
			@brief ���������� ��� ������ �������� � �������� ������ ������
			@param other ������, � ������� ��������� �������
		*/
		void onFootSensorUnCollision(PhysicObject::Collision* other);

		Animation m_animator;	// ������ ��� ��������
		float m_moveSpeed, m_jumpSpeed;	// �������� �������� � ������
		float m_desiredVelocityX;	// ��������, ������� ������� ���������� ������
		HUD m_hud;	// ����-������
		PlayerSound m_sound;	// �������� �������
		int m_currentLive, m_totalLive;	// ������� ���������� ������ � ����� ������
		int m_currentCoin, m_maxCoin;	// ������� ���������� ����� � ���������� ����� ��� ��������
	public:
		/*
			@brief ������� ������� ������
			@param source �������� �����������
			@param centerX ���������� � ������
			@param centerY ���������� � ������
			@param animator ������-��������
			@param world ���������� ���
			@param density ���������
			@param friction ������
			@param xvelocity �������� �� �
			@param yvelocity �������� �� �
			@param hud ����-������
			@param playerLive ���������� ������ � ������
			@param maxcoin ���������� �����, ���������� � ��������
		*/
		PlayerObject(	const sf::Image& source, int centerX, int centerY,
						const Animation& animator, b2World* world,
						float density, float friction,
						float xvelocity, float yvelocity,
						const HUD& hud, const PlayerSound& sound, 
						int playerLive, int maxCoin);

		PlayerObject(const PlayerObject& other) = default;
		PlayerObject& operator=(const PlayerObject& other) = default;
		virtual ~PlayerObject() = default;

		/*
			@brief ������ ��� ������� ���
		*/
		PhysicObject::Collision m_footSensorCollision;

		/*
			@brief ��������� ����������� ������
			@param render ������ ��� �������
		*/
		void controlView(sf::RenderWindow& render);
		/*
			@brief ��������� ����������
		*/
		virtual void draw(sf::RenderWindow& render) override;
		/*
			@brief ��������� �������� � ����������� �� ��������
			@param delta ����� ����� � ��������
		*/
		virtual void animate(float delta) override;
		/*
			@brief ���������� ���������� ������� ��������
			@param delta ����� ����� � ��������
		*/
		virtual void logic(float delta) override;
		/*
			@brief ���������� ��� ���������� �������
			@param live ������ � �����
			@param coin ������ � �������
		*/
		virtual void effect(int live, int coin) override;
		/*
			@brief ��������� ���������� HUD ����������
			@param render ������ ��� ���������
		*/
		void drawHUD(sf::RenderWindow& render);
		/*
			@brief ��������� ������� ��������
			@ret   ������� �� �������
		*/
		bool isWin();
		/*
			@brief ��������� ������� ���������
			@ret   �������� �� �������
		*/
		bool isFail();
	};
	//////////////////////////////////////////////////////////////////////////
}

#endif // !OBJECT_H
