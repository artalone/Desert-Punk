#include "PipeManager.h"

#include "../Engine/Engine.h"
#include "../Engine/Physics/Rigidbody.h"
#include "../FlappyTwitch/Pipe.h"
#include "Windows.h"
#include "MMSystem.h"
#include <iostream>
using namespace std;

PipeManager::PipeManager() :
	xStartSeparation(10),
	yStartSeparation(500),
	xSeparation(xStartSeparation),
	ySeparation(yStartSeparation),
	minXSeparation(300),
	minYSeparation(300),
	xSeparationSpeed(10),
	ySeparationSpeed(10),
	minSpawnY(284),
	maxSpawnY(Engine::SCREEN_HEIGHT - 284),
	totalPipes(0),
	points(0)
{
	Pipe::Initialize(false);
	CreatePipe();
}

PipeManager::~PipeManager()
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		delete pipes[i];
	}
}

void PipeManager::Update()
{
	vector<int> pipesToDelete;
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		pipes[i]->Update();
		if (pipes[i]->GetX() < -(pipes[i]->GetWidth() / 2))
		{
			pipesToDelete.push_back(i);
		}

		if (i == pipes.size() - 1)
		{
			if (pipes[i]->GetX() < Engine::SCREEN_WIDTH - xSeparation)
			{
				CreatePipe();
			}
		}

		if (pipes[i]->GetX() < Engine::SCREEN_WIDTH / 2 &&
			pipes[i]->GetPrevPos() > Engine::SCREEN_WIDTH / 2)
		{			
			points++;
			
			PlaySound(TEXT("Horn.wav"), NULL, SND_ASYNC);
		}
	}

	for (unsigned int i = 0; i < pipesToDelete.size(); i++)
	{
		delete pipes[pipesToDelete[i]];
		pipes.erase(pipes.begin() + pipesToDelete[i]);
	}

	cout << "Points: " << points << endl;
}

void PipeManager::Render()
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		pipes[i]->Render();
	}
}

bool PipeManager::CheckCollision(Flapper& flapper)
{
	bool isColliding = false;

	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		isColliding =	Rigidbody::IsColliding(flapper.GetRB(), pipes[i]->GetTopRB()) || 
						Rigidbody::IsColliding(flapper.GetRB(), pipes[i]->GetBotRB());
		if (isColliding)
			
			break;
	}

	return isColliding;
}

void PipeManager::Reset()
{
	for (unsigned int i = 0; i < pipes.size(); i++)
	{
		delete pipes[i];
	}
	pipes.clear();

	xSeparation = xStartSeparation;
	ySeparation = yStartSeparation;
	totalPipes = 0;
	points = 0;

	CreatePipe();
}

int PipeManager::GetTotalPipes() {
	return totalPipes;
}

// Private

void PipeManager::CreatePipe()
{	
	if (totalPipes % 5 == 0) {
		float spawnY = (rand() % minSpawnY) + minSpawnY;
		Pipe::Initialize(true);
		Pipe* pipe = new Pipe(Vector3(Engine::SCREEN_WIDTH, spawnY, 0), points, true);
		pipe->SetGap(0);

		pipes.push_back(pipe);
		totalPipes++;
	}
	else {
		float spawnY = (maxSpawnY - minSpawnY) + minSpawnY;
		Pipe::Initialize(false);
		Pipe* pipe = new Pipe(Vector3(Engine::SCREEN_WIDTH, spawnY, 0), points, false);
		pipe->SetGap(ySeparation);

		pipes.push_back(pipe);
		totalPipes++;
	}
}