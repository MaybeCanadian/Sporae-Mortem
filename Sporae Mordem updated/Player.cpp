#include "Player.h"

void Player::keyboardmovement()
{
	if (InputManager::getInstance().getMouseState(2) == true)
	{
		sneaking = true;
		speed = 1;
		sightDetectRange = 50;
	}
	else
	{
		sneaking = false;
		speed = 5;
		sightDetectRange = 200;
	}

	if (InputManager::getInstance().KeyDown(keybinds[0]))
	{
		moveUP();
	}
	if (InputManager::getInstance().KeyDown(keybinds[1]))
	{
		moveDOWN();
	}
	if (InputManager::getInstance().KeyDown(keybinds[2]))
	{
		moveLEFT();
	}
	if (InputManager::getInstance().KeyDown(keybinds[3]))
	{
		moveRIGHT();
	}

	if (!(InputManager::getInstance().KeyDown(keybinds[0]) || InputManager::getInstance().KeyDown(keybinds[1]) || InputManager::getInstance().KeyDown(keybinds[2]) || InputManager::getInstance().KeyDown(keybinds[3])))
	{
		stopSound();
	}
}

void Player::controllermovement()
{
}

Player::Player(int x, int y, int type, int id, int sound)
{
	m_dst.x = x;
	m_dst.y = y;
	m_dst.h = 25;
	m_dst.w = 25;
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	control_type = 1;
	setDefaultinds();
	speed = 2;
	SDL_WarpMouseInWindow(NULL, 0, 0);
	TextureID = id;
	SoundID = sound;
	chanel = -1;
	hasKey = false;
	sneaking = false;
	footstepcounter = 0;
	footsteprad = 40;
	sightDetectRange = 200;
}

Player::~Player()
{
}

void Player::setControlType(int type)
{
	control_type = type;
}

void Player::setKeybinds(SDL_Scancode * input)
{
	for (int i = 0; i < 4; i++)
		keybinds[i] = input[i];
}

void Player::setDefaultinds()
{
	keybinds[0] = SDL_SCANCODE_W;
	keybinds[1] = SDL_SCANCODE_S;
	keybinds[2] = SDL_SCANCODE_A;
	keybinds[3] = SDL_SCANCODE_D;
}

SDL_Rect* Player::getRect()
{
	return &m_dst;
}

double Player::getRotation()
{
	SDL_Point buffer = { m_dst.x + m_dst.w / 2, m_dst.y + m_dst.h / 2 };
	if (mouseX != m_dst.x)
		return UTIL::Rotation(InputManager::getInstance().getMouse(), &buffer);
	else
		std::cout << rotation << std::endl;
		return 0;
}

void Player::update()
{
	if (control_type == 1)
	{
		keyboardmovement();
		mouseAttack();
	}
	else if (control_type == 2)
		controllermovement();
	else
		std::cout << "error" << std::endl;

}

void Player::render()
{
	TextureManager::getInstance().DrawEx(TextureID, &m_dst, NULL, rotation * 180 / 3.14 + 90, NULL, SDL_FLIP_NONE);
}

void Player::respawn()
{
	m_dst = { 30, 30 };
}

void Player::setPos(int x, int y)
{
	m_dst.x = x;
	m_dst.y = y;
}

void Player::setHasKey(bool input)
{
	hasKey = input;
}

bool Player::getHadKey()
{
	return hasKey;
}

double Player::getDetctRange()
{
	return sightDetectRange;
}

void Player::moveUP()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.y -= speed;
	if (!LevelManager::getInstance().checkWallNear(&future) && future.y > 0 && !ObjectManager::getInstance().getLocked()->checkNearLocked(&future, hasKey, 1))
	{
		m_dst.y -= speed;
		playSound();
	}
}

void Player::moveDOWN()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.y += speed;
	if (!LevelManager::getInstance().checkWallNear(&future) && future.y < HEIGHT && !ObjectManager::getInstance().getLocked()->checkNearLocked(&future, hasKey, 1))
	{
		m_dst.y += speed;
		playSound();
	}
}

void Player::moveLEFT()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.x -= speed;
	if (!LevelManager::getInstance().checkWallNear(&future) && future.x > 0 && !ObjectManager::getInstance().getLocked()->checkNearLocked(&future, hasKey, 1))
	{
		m_dst.x -= speed;
		playSound();
	}
}

void Player::mouseAttack()
{
	rotation = getRotation();
	if (InputManager::getInstance().getMouseClick(0))
		ObjectManager::getInstance().getProjectileManager()->addRock(m_dst.x, m_dst.y, rotation);
}

void Player::playSound()
{
	if (chanel != -1)
	{
		if (!AudioManager::getInstance().chanelActive(chanel))
		{
			chanel = AudioManager::getInstance().playSound(SoundID, -1, -1);
		}
	}
	else
	{
		chanel = AudioManager::getInstance().playSound(SoundID, -1, -1);
	}

	//play ingame sound hear.
	if (sneaking == true)
	{
		if (AudioManager::getInstance().chanelActive(chanel))
		{
			AudioManager::getInstance().changeVolume(chanel, MIX_MAX_VOLUME / 8);
		}

		if (footstepcounter > 10)
		{
			footstepcounter = 0;
			ObjectManager::getInstance().getSoundManager()->soundsCreate((m_dst.x + m_dst.w / 2), (m_dst.y + m_dst.h / 2), footsteprad / 2, 1);
		}
		else
			footstepcounter++;
	}
	else
	{
		if (AudioManager::getInstance().chanelActive(chanel))
		{
			AudioManager::getInstance().changeVolume(chanel, MIX_MAX_VOLUME);
		}
		if (footstepcounter > 5)
		{
			footstepcounter = 0;
			ObjectManager::getInstance().getSoundManager()->soundsCreate((m_dst.x + m_dst.w / 2), (m_dst.y + m_dst.h / 2), footsteprad, 1);
		}
		else
			footstepcounter++;
	}
}

void Player::stopSound()
{
	if (chanel != -1)
	{
		if (AudioManager::getInstance().chanelActive(chanel))
		{
			AudioManager::getInstance().fadeChanel(chanel, 200);
		}
	}
}

void Player::moveRIGHT()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.x += speed;
	if (!LevelManager::getInstance().checkWallNear(&future) && future.x < WIDTH && !ObjectManager::getInstance().getLocked()->checkNearLocked(&future, hasKey, 1))
	{
		m_dst.x += speed;
		playSound();
	}
}


