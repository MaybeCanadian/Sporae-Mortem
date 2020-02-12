#include "Player.h"

void Player::keyboardmovement(SDL_Scancode* binds)
{
	if (Engine::getInstance().keyDown(binds[0]))
	{
		if (m_dst.y > 0 && check('w'))
			m_dst.y -= speed;
	}
	if (Engine::getInstance().keyDown(binds[1]))
	{
		if (m_dst.y < HEIGHT - m_dst.h && check('s'))
			m_dst.y += speed;
	}
	if (Engine::getInstance().keyDown(binds[2]))
	{
		if (m_dst.x > 0 && check('a'))
			m_dst.x -= speed;
	}
	if (Engine::getInstance().keyDown(binds[3]))
	{
		if (m_dst.x - m_dst.w < WIDTH && check('d'))
			m_dst.x += speed;
	}
}

void Player::controllermovement()
{
}

void Player::mousemovement()
{
	SDL_GetMouseState(&mouseX, &mouseY);
	if (mouseX != m_dst.x) 
		rotation = (180/3.14) * atan2(((m_dst.y + m_dst.h/2) - mouseY), ((m_dst.x + m_dst.w/2) - mouseX));
	else
		rotation = 0;
}

Player::Player(vector<SDL_Rect> v)
{
	m_dst.x = STARTPOINTX;
	m_dst.y = STARTPOINTY;
	m_dst.h = PLAYERSIZE;
	m_dst.w = PLAYERSIZE;
	control_type = 1;
	setDefaultinds();
	speed = 5;
	mouseX = 0;
	mouseY = 0;
	SDL_WarpMouseInWindow(NULL, 0, 0);
	setWallVec(v);
	texture = "prisoner.png";
	TextureID = TextureManager::getInstance().addTexture(texture);
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

void Player::setWallVec(vector<SDL_Rect> v)
{
	wallVec = v;
}

SDL_Rect Player::getRect()
{
	return m_dst;
}

double Player::getRotation()
{
	return rotation;
}

void Player::update()
{
	if (control_type == 1)
	{
		keyboardmovement(keybinds);
		mousemovement();
	}
	else if (control_type == 2)
		controllermovement();
	else
		cout << "error" << endl;
}

void Player::render()
{
	TextureManager::getInstance().Draw(TextureID, &m_dst, NULL, rotation - 90, NULL, SDL_FLIP_NONE);
}

bool Player::check(char wsad)
{
	Map map(wallVec);
	map.setWSAD(m_dst);
	return map.notHitBound(m_dst,wsad,SPEED);
}

bool Player::touchEnemy(SDL_Rect e)
{
	return (!((m_dst.x > e.x + e.w) ||
		(m_dst.x + m_dst.w < e.x) ||
		(m_dst.y + m_dst.h < e.y) ||
		(m_dst.y > e.y + e.h)));
}

void Player::respawn()
{
	m_dst = { STARTPOINTX,STARTPOINTY,PLAYERSIZE,PLAYERSIZE };
}


