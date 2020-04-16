#include "Player.h"

void Player::keyboardmovement()
{
	if (InputManager::getInstance().getMouseState(2) == true)
	{
		sneaking = true;
		maxVel = 1;
		sightDetectRange = 50;
	}
	else
	{
		sneaking = false;
		maxVel = 4;
		sightDetectRange = 200;
	}

	if (InputManager::getInstance().KeyDown(keybinds[0]))
	{
		accely = accely - accel;
		playSound();
	}
	if (InputManager::getInstance().KeyDown(keybinds[1]))
	{
		accely = accely + accel;
		playSound();
	}
	if (InputManager::getInstance().KeyDown(keybinds[2]))
	{
		accelx = accelx - accel;
		playSound();
	}
	if (InputManager::getInstance().KeyDown(keybinds[3]))
	{
		accelx = accelx + accel;
		playSound();
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
	m_dst.h = 30;
	m_dst.w = 30;
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	control_type = 1;
	setDefaultinds();
	speed = 1;
	SDL_WarpMouseInWindow(NULL, 0, 0);
	TextureID = id;
	SoundID = sound;
	chanel = -1;
	hasKey = false;
	sneaking = false;
	footstepcounter = 0;
	footsteprad = 80;
	sightDetectRange = 200;
	accelx = accely = velx = vely = 0;

	accel = 5;

	maxAccel = 10;
	maxVel = 5;
	drag = 0.9;
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

	move();

	ObjectManager::getInstance().getLocked()->checkNearLocked(&m_dst, hasKey, 1);

	accelx = accely = 0;

}

void Player::render()
{
	if (engine::getInstance().getMode() == 0)
	{
		TextureManager::getInstance().DrawEx(TextureID, &m_dst, NULL, rotation * 180 / 3.14 + 90, NULL, SDL_FLIP_NONE);
	}
	else if(engine::getInstance().getMode() ==1)
	{
		TextureManager::getInstance().DrawEx(0, &m_dst, NULL, rotation * 180 / 3.14 + 90, NULL, SDL_FLIP_NONE);
	}
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

void Player::move()
{
	accelx = UTIL::min(UTIL::max(accelx, -maxAccel), maxAccel);
	accely = UTIL::min(UTIL::max(accely, -maxAccel), maxAccel);

	velx = (velx + accelx) * drag;
	vely = (vely + accely) * drag;

	velx = UTIL::min(UTIL::max(velx, -maxVel), maxVel);
	vely = UTIL::min(UTIL::max(vely, -maxVel), maxVel);

	m_dst.x = m_dst.x + (int)velx;
	m_dst.y = m_dst.y + (int)vely;


	checkCollisions();
	
}

void Player::checkCollisions()
{
	for (int i = 0; i < LevelManager::getInstance().getWallNum(); i++)
	{
		if (UTIL::AABBcollide(&m_dst, LevelManager::getInstance().getWall(i)->getRect()))
		{
			correctcollision(LevelManager::getInstance().getWall(i)->getRect());
			break;
		}
	}

}

void Player::correctcollision(SDL_Rect * plat)
{
	if (m_dst.y + m_dst.w - vely <= plat->y)
	{
		m_dst.y = plat->y - m_dst.h - 1;
		vely = 0;
	}
	if (m_dst.y - vely >= plat->y + plat->h)
	{
		m_dst.y = plat->y + plat->h + 1;
		vely = 0;
	}
	if (m_dst.x + m_dst.w - velx <= plat->x)
	{
		m_dst.x = plat->x - m_dst.w - 1;
		velx = 0;
	}
	if (m_dst.x - velx >= plat->x + plat->w)
	{
		m_dst.x = plat->x + plat->w + 1;
		velx = 0;
	}
}

