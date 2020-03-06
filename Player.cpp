#include "Player.h"

void Player::keyboardmovement()
{
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
}

void Player::controllermovement()
{
}


Player::Player(int x, int y, int type)
{
	m_dst.x = x;
	m_dst.y = y;
	m_dst.h = 10;
	m_dst.w = 10;
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	control_type = 1;
	setDefaultinds();
	speed = 1;
	SDL_WarpMouseInWindow(NULL, 0, 0);
	texture = "prisoner.png";
	textureID = TextureManager::getInstance().addTexture(texture);
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
	//TextureManager::getInstance().DrawEx(TextureID, &m_dst, NULL, rotation - 90, NULL, SDL_FLIP_NONE);
	TextureManager::getInstance().SetDrawColor(0, 255, 255, 255);
	TextureManager::getInstance().FillRect(&m_dst);
}

void Player::respawn()
{
	m_dst = { 30, 30 };
}

void Player::moveUP()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.y -= speed;
	//if (!ObjectManager::getInstance().checkCollideWallNear(&future) && future.y > 0)
		m_dst.y -= speed;
}

void Player::moveDOWN()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.y += speed;
	//if (!ObjectManager::getInstance().checkCollideWallNear(&future) && future.y < HEIGHT)
		m_dst.y += speed;
}

void Player::moveLEFT()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.x -= speed;
	//if (!ObjectManager::getInstance().checkCollideWallNear(&future) && future.x > 0)
		m_dst.x -= speed;
}

void Player::mouseAttack()
{
	if (InputManager::getInstance().getMouseClick(0))
	{
		ObjectManager::getInstance().getProjectileManager()->addRock(m_dst.x, m_dst.y, getRotation());
	}
}

void Player::moveRIGHT()
{
	future = { m_dst.x, m_dst.y, m_dst.h, m_dst.w };
	future.x += speed;
	//if (!ObjectManager::getInstance().checkCollideWallNear(&future) && future.x < WIDTH)
		m_dst.x += speed;
}


